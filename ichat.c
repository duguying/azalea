/// @file ichat.c
/// @brief Core
/// @author Rex Lee duguying2008@gmail.com
/// @version 0.01
/// @date 2013-10-19
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <dlfcn.h>
#include "ichat.h"
#include "pool/pool.h"

//thread id
pthread_t ntid;//connect listening thread id
pthread_t mtid;//model load thread id
pthread_t ptid;//pipe listening thread id

//socket server address
struct sockaddr_in servaddr;
struct sockaddr_in clientaddr;

//socket id
int skt;

//thread connect son socket temparay id
int son_skt;

//pipe in
int pi[2];
//pipe out
int po[2];

//////////////////////////////////////////////////////////////////////

//组装信息
Msg* message(Msg* packed_msg, char* message, int to_id, int from_skt)
{
	Msg m;
	memset(packed_msg, 0, sizeof(Msg)+1);
	packed_msg->to_id = to_id;
	packed_msg->from = from_skt;
	strcpy(packed_msg->message,message);

	return packed_msg;
}

//////////////////////////socket//////////////////////////////////////

/// @brief socket_listen socket listen to connect
///
/// @return 
int socket_listen()
{
	memset(&servaddr, ECF, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(PORT);
	skt=socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	bind(skt, (struct sockaddr*)&servaddr, sizeof(servaddr));
	return listen(skt, 10);
}

/// @brief sock_listen socket connect and listen to read sock message, *thread function
/// 
/// @param arg
///
/// @return void*0 
void* sock_listen(void *arg)
{
	int pooled=0;//if saved in pool is 1, else 0
	Msg packed_msg;
	
	char pipe_buffer[PPB_LEN];
	memset(&packed_msg, ECF, sizeof(Msg));	

	//The function recv could block thread
	for(;1;){// in here, we shuold build a send model
		int rc,strleng;
		char tmpchar[20];//temprary chars
		//connect ended or error, exit
		if(recv(son_skt, packed_msg.message, BUF_LEN, 0)<=0){//recved and put it into packed msg
			break;
		};
		
		strncpy(tmpchar,packed_msg.message,1);	//if is "$lijun"	TODO&TODO&TODO Parse connection command
		if((!pooled)&&(!strcmp("$", tmpchar))){	//0 and $ start, now save in pool
			memset(&tmpchar, 0, sizeof(char)*20);
			strncpy(tmpchar, packed_msg.message, 20);
			pool_save((tmpchar+1), son_skt);	//save "lijun"
		}

		packed_msg.to_id=15;
		packed_msg.from=son_skt;
		//message(&packed_msg, sock_buffer, 1, son_skt);//TODO set 1 as a user id
		memcpy(pipe_buffer, (char*)(&packed_msg), sizeof(Msg));

		printf("packed msg: %s, length: %u \n", (char*)(&packed_msg), (sizeof(packed_msg)/sizeof(char)));//packed msg shown as char

		//pipe_buffer_set(pipe_buffer, PPB_LEN);//set pipe buffer interruption char 
		//pipe_buffer[PPB_LEN]=13;//set interruption
		printf("sock recv: %s,%u: %s\n",inet_ntoa(clientaddr.sin_addr),ntohs(clientaddr.sin_port), packed_msg.message);
		//send buffer into pipe
		
		//printf("pipe send: %s", (char*)pipe_buffer);
		rc = write(pi[1], pipe_buffer, PPB_LEN);//!TODO DO NOT send the msg pointer, send the msg, here need to be change
		

		if( rc == -1 ){
	      perror ("Parent: write");
	      close(pi[1]);
	      exit(1);
	    }
		
		memset(packed_msg.message, ECF, sizeof(char)*BUF_LEN);
	}
	
	printf("%s,%u: Disconnected!\n",inet_ntoa(clientaddr.sin_addr),ntohs(clientaddr.sin_port));
	//here the thread is exit
	return ((void *) 0);
}

/////////////////////////pipe/////////////////////////////////////////

/// @brief pipe_listen listen the pipe, when recv msg, send it
/// *thread; run in new thread
/// @return void*0
void* pipe_listen(void* arg)
{

	//cause of this is a single thread
	//the message should contain socket id (skt_id) information or message which can get the skt_id
	//printf("father pipe");	
	int rc;
	char fa_pipe_buffer[BUF_LEN];//get 1000 char, but just one time
	memset(fa_pipe_buffer, ECF, sizeof(char)*BUF_LEN);

	while((rc = read(po[0], fa_pipe_buffer, PPB_LEN)) > 0){//!!!TODO Blocked
		//printf("son pipe recv: %s\n",bf);
		send(/*((Msg*)fa_pipe_buffer)->to_id*/15, ((Msg*)fa_pipe_buffer)->message, BUF_LEN, 0);
		memset(fa_pipe_buffer, ECF, sizeof(Msg)+1);
	}
	return ((void *) 0);
}

////////////////////////////model/////////////////////////////////////

/// @brief loadmodel load model, *thread
/// 
/// @param arg model name
///
/// @return void*0 
void* loadmodel(void* arg)
{
	//load models
	void *lib_handle;
	int (*initial)(void);
	char* error;
	const char* library="cygmysql_drv.dll";
	lib_handle=dlopen(library, RTLD_LAZY);
	if(!lib_handle){
		fprintf(stderr,"%s load failed: %s\n", library, dlerror());
		//exit(1);
	}else{
		initial=dlsym(lib_handle, "initial");
		initial();
	}
	return ((void *) 0);
}

/// @brief main main function
/// 
/// @param argc
/// @param argv
///
/// @return 
int main(int argc,char **argv)
{
	int err;
	socklen_t len;
	//dealing process id
	int pid;
	
	int fh1=log_create("test.log");
	logw("test, this is a log!\n",fh1);
	
	//pool initial
	pool_init(NULL);

	//create pipe
	pipe(pi);
	pipe(po);

	//load model in new thread
	//pthread_create(&mtid, NULL, loadmodel, NULL);

	//start listen
	socket_listen();

	//create process for message dealing task
	pid=fork();
	if(0==pid){//in son process
		close(pi[1]);//close send, use recv
		close(po[0]);//close recv, use send
		printf("son start\n");
		char pipe_buffer[PPB_LEN];
		int rc;
		while((rc = read(pi[0], pipe_buffer, PPB_LEN)) > 0){//TODO
			printf("son pipe recv: %s, from %d\n",((Msg*)pipe_buffer)->message,((Msg*)pipe_buffer)->to_id);

			//pipe_buffer[PPB_LEN]=13;
			//memcpy(pipe_buffer, (char*)(&packed_msg), sizeof(Msg));
			//printf("^%d^", sizeof(pipe_buffer));
			rc = write(po[1], pipe_buffer, PPB_LEN);	//write the recvd msg into po for sendding to sock sender
			memset(pipe_buffer, ECF, PPB_LEN);
		}
	}else{// in fahter
		close(pi[0]);//close recv, use send
		close(po[1]);//close send, use recv
		//create new thread to manage pipe listen
		err = pthread_create(&ptid, NULL, pipe_listen, NULL);
		//sock length
		len = sizeof(clientaddr);
		//loop listen and accept
		for(;1;){
			//The function `accept` can block the process, so, i need't sleep
			if(son_skt=accept(skt, (struct sockaddr*)&clientaddr, &len)){
				printf("%s,%u;skt %d: Connected!\n", inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port), son_skt);
				//send connection message into the connection pool
				//pool_conn("127.0.0.1,1234", son_skt); //arg 1 is just a test now
				//if accepted, create thread!
				err = pthread_create(&ntid, NULL, sock_listen, NULL);
			}
		}
	}

	return 0;
}
