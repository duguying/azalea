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

//组装信息
Msg* message(Msg* packed_msg, char* message, int to_id, int from_skt){
	Msg m;
	memset(packed_msg, 0, sizeof(Msg)+1);
	packed_msg->to_id = to_id;
	packed_msg->from = from_skt;
	strcpy(packed_msg->message,message);

	return packed_msg;
}

/// @brief socket_listen socket listen to connect
///
/// @return 
int socket_listen(){
	memset(&servaddr, ECF, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(PORT);
	skt=socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	bind(skt, (struct sockaddr*)&servaddr, sizeof(servaddr));
	return listen(skt, 10);
}

/// @brief pipe_listen listen the pipe, when recv msg, send it
/// *thread; run in new thread
/// @return void*0
void* pipe_listen(void* arg){

	//cause of this is a single thread, TODO
	//the message should contain socket id (skt_id) information or message which can get the skt_id
	
	int rc;
	char sock_buffer[BUF_LEN];//get 10000 char, but just one time
	memset(sock_buffer, ECF, sizeof(char)*BUF_LEN);
	//pool_get_skt TODO
	while((rc = read(po[0], sock_buffer, BUF_LEN)) > 0){
		//printf("son pipe recv: %s\n",bf);
		send(son_skt, sock_buffer, BUF_LEN*sizeof(char), 0);
		memset(sock_buffer, ECF, sizeof(char)*BUF_LEN);
	}
	return ((void *) 0);
}

/// @brief pipe_buffer_set set the buffer interruption char
///
/// @param buffer buffer pointer
/// @param buffer_length buffer length
void pipe_buffer_set(char* buffer, int buffer_length){
	int strleng=strlen(buffer);
	if(buffer_length > strleng){
		buffer[strleng+1]=13;//13 is pipe interruption
	}
}

/// @brief sock_listen socket connect and listen to read sock message, *thread function
/// 
/// @param arg
///
/// @return void*0 
void* sock_listen(void *arg){
	Msg packed_msg;
	memset(&packed_msg, 'a', sizeof(Msg));
	char pipe_buffer[sizeof(Msg)+1];//!TODO get 1017 char, number is unknown
	//The function recv could block thread
	for(;1;){// in here, we shuold build a send model
		int rc,strleng;
		//connect ended or error, exit
		if(recv(son_skt, packed_msg.message, BUF_LEN, 0)<=0){//recved and put it into packed msg
			break;
		};

		packed_msg.to_id=1;
		packed_msg.from=son_skt;
		//message(&packed_msg, sock_buffer, 1, son_skt);//TODO set 1 as a user id
		memcpy(pipe_buffer, (char*)(&packed_msg), sizeof(Msg));

		printf("packed msg: %s", (&packed_msg));//TODO@TODO@TODO@TODO message shown there, the message had not packed

		//pipe_buffer_set(pipe_buffer, sizeof(Msg)+1);//set pipe buffer interruption char 
		pipe_buffer[sizeof(Msg)]=13;
		printf("sock recv: %s,%u: %s\n",inet_ntoa(clientaddr.sin_addr),ntohs(clientaddr.sin_port), packed_msg.message);
		//send buffer into pipe
		
		//printf("pipe send: %s", (char*)pipe_buffer);
		rc = write(pi[1], pipe_buffer, sizeof(Msg)+1);//!TODO DO NOT send the msg pointer, send the msg, here need to be change
		

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

/// @brief loadmodel load model, *thread
/// 
/// @param arg model name
///
/// @return void*0 
void* loadmodel(void* arg){
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
int main(int argc,char **argv){
	int err;
	socklen_t len;
	//dealing process id
	int pid;
	
	int fh1=log_create("test.log");
	logw("test, this is a log!\n",fh1);

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
		char pipe_buffer[sizeof(Msg)+1];
		int rc;
		while((rc = read(pi[0], pipe_buffer, sizeof(Msg)+1)) > 0){//TODO
			printf("son pipe recv: %s, from %d\n",((Msg*)pipe_buffer)->message,((Msg*)pipe_buffer)->to_id);//in general, the id packed! !TODO TODO
			pipe_buffer_set(pipe_buffer, BUF_LEN);
			rc = write(po[1], pipe_buffer, sizeof(Msg));//write the recvd msg into po
			memset(pipe_buffer, ECF, sizeof(Msg));
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
				printf("%s,%u: Connected!\n", inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port));
				//send connection message into the connection pool
				//pool_conn("127.0.0.1,1234", son_skt); //arg 1 is just a test now
				//if accepted, create thread!
				err = pthread_create(&ntid, NULL, sock_listen, NULL);
			}
		}
	}

	return 0;
}
