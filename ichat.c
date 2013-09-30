#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <dlfcn.h>

//thread id
pthread_t ntid;//connect thread id
pthread_t mtid;//model thread id

//socket server address
struct sockaddr_in servaddr;
struct sockaddr_in clientaddr;

//socket id
int skt;

//thread connect son socket temparay id
int son_skt;

//buffer
char buffer[1000];

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
//*thread function
void* iconnect(void *arg){
	//The function recv could block thread
	for(;1;){
		//connect ended or error, exit
		if(recv(son_skt, buffer, 1000, 0)<=0){
			break;
		};
		printf("%s,%u: %s\n",inet_ntoa(clientaddr.sin_addr),ntohs(clientaddr.sin_port),buffer);
		memset(buffer, 0, sizeof(char)*1000);
	}
	
	printf("%s,%u: Disconnected!\n",inet_ntoa(clientaddr.sin_addr),ntohs(clientaddr.sin_port));
	//here the thread is exit
	return ((void *) 0);
}

//load model
//*thread
void* loadmodel(void* arg){
	//load models
	void *lib_handle;
	int (*initial)(void);
	char* error;
	const char* library="cyglog.dll";
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

int main(int argc,char **argv){
	int err;
	socklen_t len;
	
	//load model in new thread
	pthread_create(&mtid, NULL, loadmodel, NULL);

	//start listen
	ilisten();
	
	//sock length
	len = sizeof(clientaddr);
	//loop listen and accept
	for(;1;){
		//The function `accept` can block the process, so, i need't sleep
		if(son_skt=accept(skt, (struct sockaddr*)&clientaddr, &len)){
			printf("%s,%u: Connected!\n", inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port));
			//if accepted, create thread!
			err = pthread_create(&ntid, NULL, iconnect, NULL);
		}
	}

	return 0;
}
