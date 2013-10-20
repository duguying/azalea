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

//buffer
char buffer[BUF_LEN];

//pipe in
int pi[2];
//pipe out
int po[2];

/// @brief sock_listen socket listen
///
/// @return 
int sock_listen(){
	memset(&servaddr, ECF, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(PORT);
	skt=socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	bind(skt, (struct sockaddr*)&servaddr, sizeof(servaddr));
	return listen(skt, 10);
}

//TODO@TODO@TODO
/// @brief pipe_listen listen the pipe, when recv msg, send it
/// *thread; run in new thread
/// @return void*0
void* pipe_listen(void* arg){

	//cause of this is a single thread, TODO
	//the message should contain socket id (skt_id) information or message which can get the skt_id
	
	int rc;
	//pool_get_skt TODO
	while((rc = read(po[0], buffer, BUF_LEN)) > 0){
		//printf("son pipe recv: %s\n",bf);
		send(son_skt, buffer, BUF_LEN*sizeof(char), 0);
		memset(buffer, ECF, sizeof(char)*BUF_LEN);
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

/// @brief sock_connect socket connect, *thread function
/// 
/// @param arg
///
/// @return void*0 
void* sock_connect(void *arg){
	//The function recv could block thread
	for(;1;){// in here, we shuold build a send model
		int rc,strleng;
		//connect ended or error, exit
		if(recv(son_skt, buffer, 1000, 0)<=0){
			break;
		};
		/**
		 * Here! I have a big problem, I can not send one sock thread's socket ID to the receiver! TODO 
		 **/
		pipe_buffer_set(buffer, BUF_LEN);//set pipe buffer interruption char
		printf("sock recv: %s,%u: %s\n",inet_ntoa(clientaddr.sin_addr),ntohs(clientaddr.sin_port),buffer);
		//send buffer into pipe
		rc = write(pi[1], buffer, sizeof(char)*BUF_LEN);
		
		if( rc == -1 ){
	      perror ("Parent: write");
	      close(pi[1]);
	      exit(1);
	    }
		
		memset(buffer, ECF, sizeof(char)*BUF_LEN);
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
	sock_listen();

	//create process for message dealing task
	pid=fork();
	if(0==pid){//in son process
		close(pi[1]);//close send, use recv
		close(po[0]);//close recv, use send
		printf("son start\n");
		char bf[BUF_LEN];
		int rc;
		while((rc = read(pi[0], bf, BUF_LEN)) > 0){//TODO
			printf("son pipe recv: %s\n",bf);
			pipe_buffer_set(bf, BUF_LEN);
			rc = write(po[1], bf, sizeof(char)*BUF_LEN);//write the recvd msg into po
			memset(bf, ECF, sizeof(char)*BUF_LEN);
		}
	}else{
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
				pool_conn("127.0.0.1,1234", son_skt); //arg 1 is just a test now
				//if accepted, create thread!
				err = pthread_create(&ntid, NULL, sock_connect, NULL);
			}
		}
	}

	return 0;
}
