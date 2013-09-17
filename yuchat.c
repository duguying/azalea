#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

//thread id
pthread_t ntid;

//socket server address
struct sockaddr_in servaddr;

//socket id
int skt;

//socket listen
int yu_listen(){
	memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(6666);
	skt=socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	bind(skt, (struct sockaddr*)&servaddr, sizeof(servaddr));
	return listen(skt, 10);
}

//socket connect
void* yu_connect(void *arg){
	printf("hello, connected!\n");
	return ((void *) 0);
}

int main(int argc,char **argv){
	int err;
	
	//start listen
	yu_listen();

	//loop listen and accept
	for(;1;){
		//The function `accept` can block the process, so, i need't sleep
		if(accept(skt,NULL,NULL)){
			//if accepted, create thread!
			err = pthread_create(&ntid, NULL, yu_connect, NULL);
		}
	}

	return 0;
}
