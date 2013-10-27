/// @file tcper.c
/// @brief 
/// @author Rex Lee duguying2008@gmail.com
/// @version 0.01
/// @date 2013-9-26
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

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

/// @brief main 
/// tcper arg1[ip] arg2[port]
/// @param argc
/// @param argv 
///
/// @return success 0
int main(int argc, char** argv)
{
	int skt;
	socklen_t len;

	if(argc<=1){
		argv[1]="127.0.0.1";
		argv[2]="6666";
	}else if(argc==2){
		argv[2]="6666";
	}
    
    memset(&saddr, 0, sizeof(struct sockaddr));
    skt=socket(AF_INET, SOCK_STREAM, 0);
	
	saddr.sin_family=AF_INET;
    saddr.sin_addr.s_addr=inet_addr(argv[1]);
    saddr.sin_port=htons(atoi(argv[2]));
    
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

