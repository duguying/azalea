/**
 * Azalea Chatting Server
 *
 * Copyright (C) 2013-2015 Rex Lee <duguying2008@gmail.com>
 *
 * This program is free and opensource software; 
 * you can redistribute it and/or modify
 * it under the terms of the GNU General Public License
 */

#include <termios.h>
#include <unistd.h>
#include "ichat.h"
#include "apis/thread.h"
#include "apis/sock.h"
#include "net/message.h"
#include <sys/types.h>
#include <unistd.h>

#define IP 16
#define PORT_LEN 6

struct sockaddr_in saddr;
char buf[1000];

char * replaceAll(char * src,char oldChar,char newChar){
	char * head=src;
	while(*src!='\0'){
		if(*src==oldChar)
			*src=newChar;
		src++;
	}
	return head;
}

/**
 * socket recv message
 * @param arg the connected socket id
 */
void* listen_message(void *arg){
	int skt;
	char buf_rcv[1000];

	skt=*(int*)arg;
	for(;1;){
		if(recv(skt, buf_rcv, 1000*sizeof(char), 0)<=0){//recved and put it into packed msg
			break;
		}else{
			printf("Received: %s\n", buf_rcv);
		};
	}
	
	return ((void *) 0);
}

/**
 * @brief getch funtion
 * @details  like getch() in win32 console
 * @return the char
 */
int getch(void){
	struct termios tm,tm_old;
	int fd=STDIN_FILENO,c;
	if (tcgetattr(fd,&tm)<0)
	{
		return -1;
	}
	tm_old=tm;
	cfmakeraw(&tm);
	if (tcsetattr(fd,TCSANOW,&tm)<0)
	{
		return -1;
	}
	c=fgetc(stdin);
	if (tcsetattr(fd,TCSANOW, &tm_old)<0)
	{
		return -1;
	}
	return c;
}

void login(void){
	char user[20];
	char pass[20];
	int i=0,ch;

	printf("\033[1;34m\
================LOGIN================\033[1;0m\n");
	printf("USERNAME:");
	fgets(user,20,stdin);
	printf("PASSWORD:");
	// fgets(pass,20,stdin);
	

	while('\r'!=(ch=getch())){
		pass[i]=ch;
		printf("*");
		i++;
	}



	printf("\n");
	printf("%s:%s\n", user, pass);
}

/**
 * main function
 * @param  argc [description]
 * @param  argv [description]
 * @return      success 0
 */
int main(int argc, char** argv)
{
	SOCKET_ID skt;
	size_t len;
	char ch;
	char ip[IP];
	char port[PORT_LEN];
	Frame* frames;
	int i;

	login();

	strncpy(ip,"127.0.0.1",IP);
	strncpy(port,"6666",PORT_LEN);

    while ((ch = getopt(argc,argv,"i:p:"))!=-1){  
		switch(ch){
		case 'i':
			memset(ip,0,sizeof(char)*IP);
			strncpy(ip,optarg,IP);
			printf("option ip:'%s'\n",ip);
			break;
		case 'p':
			memset(port,0,sizeof(char)*PORT_LEN);
			strncpy(port,optarg,PORT_LEN);
			printf("option port :%s\n", port);
			break;  
		default:  
			;
		}  
	}  

    memset(&saddr, 0, sizeof(struct sockaddr));
    skt=sock_client(AF_INET, SOCK_STREAM, PROTO_TCP);
	
	saddr.sin_family=AF_INET;
    saddr.sin_addr.s_addr=inet_addr(ip);
    saddr.sin_port=htons(atoi(port));
    
	len=sizeof(struct sockaddr);
	if(sock_connect(skt, (struct sockaddr*)&saddr, len)<0){
		printf("Connected Failed!\n");
		return 0;
	}else{
		int err;
		TID tid;
		//create thread to recv message here!!!
		err = thread_create(&tid, listen_message, &skt);
		memset(buf, 0, sizeof(char)*1000);
		for(;1;){
			fgets(buf, 1000, stdin);
			replaceAll(buf,'\n','\0');
			if(0==strcmp(buf, ".exit")){
				return 0;
			}
			frames=msg_modulate(buf);
			for (i = 0; i < frames[0].tf; ++i)
			{
				send(skt, (void*)&frames[i], sizeof(Frame), 0);
				printf("[%d/%d]\n", frames[i].cf, frames[i].tf);
			}
			
		}
		
	}
	
	//TODO if the server closed the connect, shutdown

	return 0;
}

