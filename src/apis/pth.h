/**
 * Azalea Chatting Server
 *
 * Copyright (C) 2013-2015 Rex Lee <duguying2008@gmail.com>
 *
 * This program is free and opensource software; 
 * you can redistribute it and/or modify
 * it under the terms of the GNU General Public License
 */

#ifndef _PTH_H_
#define _PTH_H_

#if defined linux
	#include <pthread.h>
 	typedef pthread_t TID;
#endif
#if defined _WIN32
 	#include "windows.h"
 	typedef unsigned long int TID;
#endif

int
thread_create(
	///thread id
	TID* tid,
	///the routine function
	void* fun,
	///the arguments
	void* arg
	);


#endif