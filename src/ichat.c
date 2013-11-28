/**
 * Azalea Chatting Server
 *
 * Copyright (C) 2013-2015 Rex Lee <duguying2008@gmail.com>
 *
 * This program is free and opensource software; 
 * you can redistribute it and/or modify
 * it under the terms of the GNU General Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <dlfcn.h>
#include <getopt.h>
#include "ichat.h"
#include "pool/pool.h"
#include "ds/hashtable.h"

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
//int son_skt; //this CAN NOT be global

//pipe in
int pi[2];
//pipe out
int po[2];

//////////////////////////////////////////////////////////////////////

//package message
Msg* message(Msg* packed_msg, char* message, int to_id, int from_skt){
	Msg m;
	memset(packed_msg, 0, sizeof(Msg));
	packed_msg->to_id = to_id;
	packed_msg->from = from_skt;
	strcpy(packed_msg->message,message);

	return packed_msg;
}

//////////////////////////socket//////////////////////////////////////

/**
 * socket_listen socket listen to connect
 * @return socket id
 */
int socket_listen(){
	memset(&servaddr, ECF, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(PORT);
	skt=socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	bind(skt, (struct sockaddr*)&servaddr, sizeof(servaddr));
	return listen(skt, 10);
}

/**
 * socket connect and listen to read sock message, *thread function
 * @param arg argument
 */
void* sock_listen(void *arg){
	int pooled=0;//if saved in pool is 1, else 0
	Msg packed_msg;

	int tskt;//the socket id of this thread

	int rc,strleng;
	char tmpchar[ID_LEN];//temprary chars
	char username[ID_LEN];//username

	char pipe_buffer[PPB_LEN];
	memset(&packed_msg, ECF, sizeof(Msg));

	tskt=*(int*)arg;
	printf("tskt is %d\n", tskt);

	packed_msg.to_id=0;	//default is 0	

	//The function recv could block thread
	for(;1;){// in here, we shuold build a send model
		
		//connect ended or error, exit
		if(recv(tskt, packed_msg.message, BUF_LEN, 0)<=0){//recved and put it into packed msg
			break;
		};
		
		strncpy(tmpchar,packed_msg.message,1);
		if((!pooled)&&(!strcmp("$", tmpchar))){
			memset(&tmpchar, 0, sizeof(char)*ID_LEN);
			strncpy(tmpchar, packed_msg.message, ID_LEN);
			pool_save((tmpchar+1), tskt);
			strncpy(username,(tmpchar+1),ID_LEN);
			pooled=1;
			memset(&tmpchar, 0, sizeof(char)*ID_LEN);
		}

		if(pooled&&(!strcmp("*", tmpchar))){//TODO Here is a bug will create segment fault, when can not find the result from the hashtable, the bug appear
			int stskt;
			stskt=pool_get(packed_msg.message+1);//here the packed_msg.message+1 is username
			printf("\033[0;33myou will send to skt %d\033[0;0m\n", stskt);
			packed_msg.to_id=stskt;	//default is 0
		}
		
		
		packed_msg.from=tskt;
		
		memcpy(pipe_buffer, (char*)(&packed_msg), sizeof(Msg));

		printf("sock recv: %s,%u: %s\n",inet_ntoa(clientaddr.sin_addr),ntohs(clientaddr.sin_port), packed_msg.message);
		//send buffer into pipe
		
		//printf("pipe send: %s", (char*)pipe_buffer);
		rc = write(pi[1], pipe_buffer, PPB_LEN);
		
		if( rc == -1 ){
	      perror ("Parent: write");
	      close(pi[1]);
	      exit(1);
	    }
		
		memset(packed_msg.message, ECF, sizeof(char)*BUF_LEN);
	}
	
	pool_discon((const char*)&username);
	
	printf("\033[1;34m%s,%u;skt %d: Disconnected!\033[1;0m\n",inet_ntoa(clientaddr.sin_addr),ntohs(clientaddr.sin_port), tskt);
	//here the thread is exit
	return ((void *) 0);
}

/////////////////////////pipe/////////////////////////////////////////

/**
 * listen the pipe, when recv msg, send it
 * @param arg argument
 */
void* pipe_listen(void* arg){
	//cause of this is a single thread
	//the message should contain socket id (skt_id) information or message which can get the skt_id
	//printf("father pipe");	
	int rc;
	//int pooled=0;
	char fa_pipe_buffer[BUF_LEN];//get 1000 char, but just one time
	char tmpchar[ID_LEN];//temprary chars

	memset(fa_pipe_buffer, ECF, sizeof(char)*BUF_LEN);

	while((rc = read(po[0], fa_pipe_buffer, PPB_LEN)) > 0){//!!!Here Cannot Print Message
		//printf("son pipe recv: %s\n",bf);
		printf("to id %d\n", ((Msg*)fa_pipe_buffer)->to_id);
		if(((Msg*)fa_pipe_buffer)->to_id){
			send(((Msg*)fa_pipe_buffer)->to_id, ((Msg*)fa_pipe_buffer)->message, BUF_LEN, 0);
		}
		memset(fa_pipe_buffer, ECF, sizeof(Msg));
	}
	return ((void *) 0);
}

////////////////////////////model/////////////////////////////////////

/**
 * load model, *thread
 * @param arg model name
 */
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

int do_name, do_gf_name;
char *l_opt_arg;
struct option longopts[] = {
     { "start",no_argument,NULL,'S'},
     { "stop",no_argument,NULL,'P'},
     { "restart",no_argument,NULL,'R'},
     {      0,     0,     0,     0},
};


/**
 * main function
 * @param  argc [description]
 * @param  argv [description]
 * @return      [description]
 */
int main(int argc,char **argv){
	int err;
	socklen_t len;
	//dealing process id
	int pid;
	//son socket id
	int son_skt;
	
	int fh1=log_create("test.log");
	logw("test, this is a log!\n",fh1);
	

	int c;
    
	while((c = getopt_long(argc, argv, ":", longopts, NULL)) != -1){
		switch (c){
			case 'S':
				if(0==fork()){//son
					system("./ichat");
				}else{
					abort();
				};
				break;
			case 'P':
				printf("Her name is BX.\n");
				break;
			case 'R':
				l_opt_arg = optarg;
				printf("Our love is %s!\n", l_opt_arg);
				break;
		}
	}  
	// iprintf("hello%d",123);


	//pool initial
	Pool* pool=pool_init();

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
		while((rc = read(pi[0], pipe_buffer, PPB_LEN)) > 0){
			printf("son pipe recv: %s, from %d\n",((Msg*)pipe_buffer)->message,((Msg*)pipe_buffer)->from);

			//pipe_buffer[PPB_LEN]=13;
			//memcpy(pipe_buffer, (char*)(&packed_msg), sizeof(Msg));

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
				printf("\033[1;32m%s,%u;skt %d: Connected!\033[1;0m\n", inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port), son_skt);
				//if accepted, create thread!
				err = pthread_create(&ntid, NULL, sock_listen, &son_skt);//send the son socket
			}
		}
	}

	return 0;
}
