#include "./thread.h"
#include <windows.h>
#include <stdio.h>

DWORD WINAPI testfn(void*p){
	for(;1;){
		;
	}
}
LPDWORD tid;

int main(){
	

	thread_create(tid,testfn,NULL);
	printf("hihihi");
	return 0;
}