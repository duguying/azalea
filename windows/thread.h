#include <windows.h>
#include <stdio.h>

typedef struct _THREAD_PARAM{
	int i;
	float f;
	double d;
	char* s;
	void* p;
} THREAD_PARAM, *LPTHREAD_PARAM;

/**
 * Create Thread
 * Noparam function call
 */
HANDLE thread_create(
		LPDWORD tid,//Thread id
		LPTHREAD_START_ROUTINE tfn//Thread start function
		){
	LPTHREAD_PARAM tParam=(LPTHREAD_PARAM)HeapAlloc(GetProcessHeap(),HEAP_ZERO_MEMORY,sizeof(THREAD_PARAM));
	return CreateThread(
		NULL,
		0,
		tfn,
		tParam,
		0,
		tid
		);
}
