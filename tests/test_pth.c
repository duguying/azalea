/**
 * Azalea Chatting Server
 *
 * Copyright (C) 2013-2015 Rex Lee <duguying2008@gmail.com>
 *
 * This program is free and opensource software; 
 * you can redistribute it and/or modify
 * it under the terms of the GNU General Public License
 */

#include "apis/pth.h"

void* test_func(){
	printf("hello world, i am in thread.\n");
	for(;1;){
		//hold on the thread
	}
	
}

int main(void){
	TID tid;
	thread_create(&tid,(LPTHREAD_START_ROUTINE)test_func,NULL);
	printf("Rex, i am not in thread.\n");
	return 0;
}