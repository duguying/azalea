#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h> 

//thread id
pthread_t ntid;

//socket server address
struct sockaddr_in servaddr;
struct sockaddr_in clientaddr;

//socket id
int skt;

//thread connect son socket temparay id
int son_skt;

//buffer
char buffer[1000];

//clear buffer
void clear_buff(){
	int i=0;
	for(i=0;i<1000;i++){
		buffer[i]=0;
	}
}

//socket listen
int ilisten(){
	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(6666);
	skt=socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	bind(skt, (struct sockaddr*)&servaddr, sizeof(servaddr));
	return listen(skt, 10);
}

//socket connect
void* iconnect(void *arg){
	//The function recv could block thread
	for(;1;){
		//connect ended or error, exit
		if(recv(son_skt, buffer, 1000, 0)<=0){
			break;
		};
		printf("%s.%u: %s\n",inet_ntoa(clientaddr.sin_addr),clientaddr.sin_port,buffer);
		clear_buff();
	}
	
	printf("%s.%u: Disconnected!\n",inet_ntoa(clientaddr.sin_addr),clientaddr.sin_port);
	//here the thread is exit
	return ((void *) 0);
}

int main(int argc,char **argv){
	int err;
	socklen_t len;

	//start listen
	ilisten();
	
	//sock length
	len = sizeof(clientaddr);
	//loop listen and accept
	for(;1;){
		//The function `accept` can block the process, so, i need't sleep
		if(son_skt=accept(skt, (struct sockaddr*)&clientaddr, &len)){
			printf("%s.%u: Connected!\n", inet_ntoa(clientaddr.sin_addr), clientaddr.sin_port);
			//if accepted, create thread!
			err = pthread_create(&ntid, NULL, iconnect, NULL);
		}
	}

	return 0;
}
