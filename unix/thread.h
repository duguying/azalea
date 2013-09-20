#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int thread_create(
		pthread_t* tid,
	   	void* (*tfn)(void*),
	   	void* arg
		){
	return pthread_create(tid,NULL,tfn,arg);
}
