/**
 * Azalea Chatting Server
 *
 * Copyright (C) 2013-2015 Rex Lee <duguying2008@gmail.com>
 *
 * This program is free and opensource software; 
 * you can redistribute it and/or modify
 * it under the terms of the GNU General Public License
 */

#include "ichat.h"
#include "apis/thread.h"
#include "apis/sock.h"
#include <getopt.h>

#include "pool/pool.h"
#include "ds/hashtable.h"
#include "log/log.h"

//thread id
TID ntid;//connect listening thread id
TID mtid;//model load thread id
TID ptid;//pipe listening thread id

//socket server address
struct sockaddr_in servaddr;
struct sockaddr_in clientaddr;

//socket id
int skt;

//pipe in
int pi[2];
//pipe out
int po[2];

//////////////////////////////////////////////////////////////////////

/**
 * @brief package message
 * @details [long description]
 * 
 * @param packed_msg [description]
 * @param message [description]
 * @param to_id [description]
 * @param from_skt [description]
 * @return [description]
 */
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
 * listen whether there is a socket connet request, 
 * and put socket id into connection pool
 * @return socket id
 */
int socket_listen(){
	int bind_result;

	memset(&servaddr, ECF, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(PORT);
	skt=socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(skt<0){
		log_printf("Create socket ERROR!");
		return IERROR;
	};
	bind_result=bind(skt, (struct sockaddr*)&servaddr, sizeof(servaddr));
	if(IERROR==bind_result){
		log_printf("binding failed!\n");
		return IERROR;
	}
	return listen(skt, 10);
}

/**
 * socket connect and listen message from socket, *thread function
 * @param arg argument
 */
void* msg_listen(void *arg){
	Msg packed_msg;

	int tskt;//the socket id of this thread

	int rc,strleng;
	char tmpchar[ID_LEN];//temprary chars
	char username[ID_LEN];//username

	char pipe_buffer[PPB_LEN];
	memset(&packed_msg, ECF, sizeof(Msg));

	tskt=*(int*)arg;
	log_printf("tskt is %d\n", tskt);

	packed_msg.to_id=0;	//default is 0	

	//The function recv could block thread
	for(;1;){
		
		//connect ended or error, exit
		if(recv(tskt, packed_msg.message, BUF_LEN, 0)<=0){//recved and put it into packed msg
			break;
		};
		
		/// shake hands here
		
		memcpy(pipe_buffer, (char*)(&packed_msg), sizeof(Msg));
		log_printf("sock recv: %s,%u: %s\n",inet_ntoa(clientaddr.sin_addr),ntohs(clientaddr.sin_port), packed_msg.message);
		rc = write(pi[1], pipe_buffer, PPB_LEN);
		if( rc == -1 ){
	      perror ("Parent: write");
	      close(pi[1]);
	      exit(1);
	    }
		
		memset(packed_msg.message, ECF, sizeof(char)*BUF_LEN);
	}
	
	pool_disconnect((const char*)&username);
	
	log_printf("\033[1;34m%s,%u;skt %d: Disconnected!\033[1;0m\n",inet_ntoa(clientaddr.sin_addr),ntohs(clientaddr.sin_port), tskt);
	//here the thread is exit
	return ((void *) 0);
}

/////////////////////////pipe/////////////////////////////////////////

/**
 * listen the pipe, when recv msg, send it
 * @param arg argument
 */
void* pipe_listen(void* arg){	
	int rc;

	char fa_pipe_buffer[BUF_LEN];//get 1000 char, but just one time
	char tmpchar[ID_LEN];//temprary chars

	memset(fa_pipe_buffer, ECF, sizeof(char)*BUF_LEN);

	while((rc = read(po[0], fa_pipe_buffer, PPB_LEN)) > 0){
		log_printf("to id %d\n", ((Msg*)fa_pipe_buffer)->to_id);
		if(((Msg*)fa_pipe_buffer)->to_id){
			send(((Msg*)fa_pipe_buffer)->to_id, ((Msg*)fa_pipe_buffer)->message, BUF_LEN, 0);//socket send message
		}
		memset(fa_pipe_buffer, ECF, sizeof(Msg));
	}
	return ((void *) 0);
}

/**
 * main function
 * @param  argc [description]
 * @param  argv [description]
 * @return      [description]
 */
int main(int argc,char **argv){
	///create thread result
	int create_thread_result;
	///create pipe result
	int create_pipe1_result,create_pipe2_result;
	size_t len;
	///father pid to start service
	int main_pid;
	//dealing process id
	int pid,son_pid;
	//son socket id
	int son_skt;
	///pid log file handle
	FILE* pid_log_file_handle;

	log_create("ichat.log");

 /////////////////////
	///The main process ended, and then, the son adopt by init

 	main_pid=fork();
 	if (main_pid<0)
 	{
 		printf("create process failed! service have NOT start!\n");
 		return IERROR;
 	}else if (main_pid>0)//in father
 	{
 		printf("ichat(%d) started...\n",main_pid);
 		///write the pid into file
 		pid_log_file_handle=fopen(PIDF,"w");
 		fprintf(pid_log_file_handle,"%d\n",main_pid);
 		fclose(pid_log_file_handle);
 		exit(0);//in father
 	}else if(main_pid==0){
//////////////////////

		//pool initial
		Pool* pool=pool_init();

		//create pipe
		create_pipe1_result=pipe(pi);
		create_pipe2_result=pipe(po);
		if(create_pipe1_result==IERROR||create_pipe2_result==IERROR){
			log_printf("create pipe failed!\n");
			return IERROR;
		}

		//start listen
		if(IERROR==socket_listen()){
			return IERROR;
		};

		//create process for message dealing task
		pid=fork();
		if(IERROR==pid){
			log_printf("create process failed!\n");
			return IERROR;
		}
		if(0==pid){//in son process
			close(pi[1]);//close send, use recv
			close(po[0]);//close recv, use send
			char pipe_buffer[PPB_LEN];
			int rc;
			while((rc = read(pi[0], pipe_buffer, PPB_LEN)) > 0){
				log_printf("son pipe recv: %s, from %d\n",((Msg*)pipe_buffer)->message,((Msg*)pipe_buffer)->from);
				rc = write(po[1], pipe_buffer, PPB_LEN);	//write the recvd msg into po for sendding to sock sender
				memset(pipe_buffer, ECF, PPB_LEN);
			}
		}else{// in fahter
			log_printf("son(%d) start\n",pid);
	 		///close the extra pipe port
			close(pi[0]);
			close(po[1]);
			//create new thread to manage pipe listen
			create_thread_result = thread_create(&ptid, pipe_listen, NULL);
			if(create_thread_result!=0){
				log_printf("create thread error!\n");
				return IERROR;
			}
			//sock length
			len = sizeof(clientaddr);
			//loop listen and accept
			for(;1;){
				//The function `accept` can block the process, so, i need't sleep
				if(son_skt=sock_accept(skt, (struct sockaddr*)&clientaddr, &len)){
					log_printf("\033[1;32m%s,%u;skt %d: Connected!\033[1;0m\n", inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port), son_skt);
					//if accepted, create thread!
					create_thread_result = thread_create(&ntid, msg_listen, &son_skt);//send the son socket
					if(create_thread_result!=0){
						log_printf("create thread error!\n");
						return IERROR;
					}
				}
			}
		}

///////////////////////
	}
 	return 0;
///////////////////////

}
