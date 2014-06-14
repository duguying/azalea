/**
 * Azalea Chatting Server
 *
 * Copyright (C) 2013-2015 Rex Lee <duguying2008@gmail.com>
 *
 * This program is free and opensource software; 
 * you can redistribute it and/or modify
 * it under the terms of the GNU General Public License
 */

#include "apis.h"

#if defined _WIN32
 	#include <windows.h>
 	#define PIPE_NAME ("\\\\.\\pipe\\Azalea")
#else
 	// 
#endif

az_exp int process_create();

az_exp void pipe_create();

az_exp void pipe_write();

az_exp void pipe_read();

az_exp void pipe_close();

