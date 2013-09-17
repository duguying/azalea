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

//thread connect son socket temparay id
int son_skt;

//buffer
char buffer[1000];

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
	send(son_skt, "hello!", 7, 0);
	printf("hello, connected!\n");
	/*for(;1;){
		recv(son_skt, buffer, 1000, 0);
		printf("%s",buffer);
		sleep(1);
	}*/

	return ((void *) 0);
}

int main(int argc,char **argv){
	int err;
	
	//start listen
	yu_listen();

	//loop listen and accept
	for(;1;){
		//The function `accept` can block the process, so, i need't sleep
		if(son_skt=accept(skt,NULL,NULL)){
			//if accepted, create thread!
			err = pthread_create(&ntid, NULL, yu_connect, NULL);
		}
	}

	return 0;
}
