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

#if defined _WIN32
 	#include <windows.h>
 	#define PIPE_NAME ("\\\\.\\pipe\\Azalea")
#else
 	// 
#endif

int process_create();

void pipe_create();

void pipe_write();

void pipe_read();

void pipe_close();

