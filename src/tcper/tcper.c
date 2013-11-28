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
#include <unistd.h>

#define IP 16
#define PORT 6

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
 * main function
 * @param  argc [description]
 * @param  argv [description]
 * @return      success 0
 */
int main(int argc, char** argv)
{
	int skt;
	socklen_t len;
	char ch;
	char ip[IP];
	char port[PORT];

	strncpy(ip,"127.0.0.1",IP);
	strncpy(port,"6666",PORT);

    while ((ch = getopt(argc,argv,"i:p:"))!=-1){  
		switch(ch){
		case 'i':
			memset(ip,0,sizeof(char)*IP);
			strncpy(ip,optarg,IP);
			printf("option ip:'%s'\n",ip);
			break;
		case 'p':
			memset(port,0,sizeof(char)*PORT);
			strncpy(port,optarg,PORT);
			printf("option port :%s\n", port);
			break;  
		default:  
			;
		}  
	}  

    memset(&saddr, 0, sizeof(struct sockaddr));
    skt=socket(AF_INET, SOCK_STREAM, 0);
	
	saddr.sin_family=AF_INET;
    saddr.sin_addr.s_addr=inet_addr(ip);
    saddr.sin_port=htons(atoi(port));
    
	len=sizeof(struct sockaddr);
    
	if(connect(skt, (struct sockaddr*)&saddr, len)<0){
        printf("Connected Failed!\n");
        return 0;
    }else{
		for(;1;){
			memset(buf, 0, sizeof(char)*1000);
			fgets(buf, 1000, stdin);
			replaceAll(buf,'\n','\0');
			if(0==strcmp(buf, ".exit")){
				return 0;
			}
			send(skt, buf, 1000*sizeof(char), 0);
		}
	};
	//TODO if the server closed the connect, shutdown

    return 0;
}

