/**
 * Azalea Chatting Server
 *
 * Copyright (C) 2013-2015 Rex Lee <duguying2008@gmail.com>
 *
 * This program is free and opensource software; 
 * you can redistribute it and/or modify
 * it under the terms of the GNU General Public License
 */

#include "ichat.h"
#include "pth.h"

int
thread_create(
	///thread id
	TID* tid,
	///the routine function
	void* fun,
	///the arguments
	void* arg
	){
#if defined _WIN32
	HANDLE create_thread_result;
	create_thread_result=CreateThread(NULL,0,fun,arg,0,tid);
	if(NULL==create_thread_result){
		return ERROR;
	}else{
		return OK;
	}
#endif
}





