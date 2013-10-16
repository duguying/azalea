#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <dlfcn.h>

#define BUF_LEN 1000 //buffer length
#define PORT 6666 //port
#define ECF 0 //Empty Char Fill

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
char buffer[BUF_LEN];

//pipe
int pp[2];

//socket listen
int ilisten(){
	memset(&servaddr, ECF, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(PORT);
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
		//printf("%s,%u: %s\n",inet_ntoa(clientaddr.sin_addr),ntohs(clientaddr.sin_port),buffer);
		//send buffer into pipe TODO
		write(pp[1], buffer, sizeof(char)*BUF_LEN);
		memset(buffer, ECF, sizeof(char)*BUF_LEN);
		//close(pp[1]);
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

//main function
int main(int argc,char **argv){
	int err;
	socklen_t len;
	//dealing process id
	int pid;
	
	int fh1=log_create("test.log");
	logw("test, this is a log!\n",fh1);

	//create pipe TODO
	pipe(pp);

	//load model in new thread
	//pthread_create(&mtid, NULL, loadmodel, NULL);

	//start listen
	ilisten();

	//create process for message dealing task
	pid=fork();
	if(0==pid){//in son process
		//sleep(3);//wait 3 sec for father's listening task begin
		//TODO
		char bf[BUF_LEN];
		int i;
		//for(i=0;i<3;i++){
			//sleep(10);
			memset(bf, ECF, sizeof(char)*BUF_LEN);
			read(pp[0],bf,BUF_LEN);
			printf("%s",bf);
						memset(bf, ECF, sizeof(char)*BUF_LEN);
			read(pp[0],bf,BUF_LEN);
			printf("%s",bf);
		//}
		
		//getchar();
	}else{
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
	
	}

	

	return 0;
}
