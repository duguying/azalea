#include <windows.h>
#include <stdio.h>

/**
 * Create Thread
 * Noparam function call
 */
HANDLE thread_create(
		LPDWORD tid,//Thread id
		LPTHREAD_START_ROUTINE tfn,//Thread start function
		void* tParam//Start function param struct
		){
	return CreateThread(
		NULL,
		0,
		tfn,
		tParam,
		0,
		tid
		);
}
