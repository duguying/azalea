#include "./thread.h"
#include <windows.h>
#include <stdio.h>

DWORD WINAPI testfn(LPVOID lpParam){
	for(;1;){
		;
	}
}
LPDWORD tid;

int main(){
	

	thread_create(tid,testfn);
	printf("hihihi");
	return 0;
}