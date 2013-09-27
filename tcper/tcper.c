/* 
 * File:   tcper.c
 * Author: rex
 * Client Tcp Tester
 * Created on 2013/9/26/, 8:26pm
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

struct sockaddr_in saddr;
char buf[1000];

//clear buffer
void clear_buff(){
	int i=0;
	for(i=0;i<1000;i++){
		buf[i]=0;
	}
}

/*
 * client tcp tester
 * tcper arg1[ip] arg2[port]
 */
int main(int argc, char** argv) {
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
    
	if(connect(skt, &saddr, len)<0){
        printf("Connected Failed!\n");
        return 0;
    }else{
		for(;1;){
			clear_buff();
			scanf("%s", buf);
			if(0==strcmp(buf, ".exit")){
				return 0;
			}
			send(skt, buf, 1000*sizeof(char), 0);
		}
	};
	//TODO if the server closed the connect, shutdown

    return 0;
}

