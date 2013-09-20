#include <stdio.h>
#include "thread.h"

void* th_func(void* p){
	for(;1;){}
	return (void*)0;
}

int main(void){
	pthread_t tid;
	thread_create(&tid,th_func,NULL);
	printf("hihihi");
	return 0;
}
