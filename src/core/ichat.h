/**
 * Azalea Chatting Server
 *
 * Copyright (C) 2013-2015 Rex Lee <duguying2008@gmail.com>
 *
 * This program is free and opensource software; 
 * you can redistribute it and/or modify
 * it under the terms of the GNU General Public License
 */

#ifndef _ICHAT_H_
#define _ICHAT_H_

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include "message.h"
#include "common.h"

///username and etc name
#define ID_LEN 20
///port
#define PORT 6666 
///Empty Char Fill
#define ECF 0 
///pid file
#define PIDF "pid"

///user node in the connection pool
typedef struct _UserNode
{
	///user thread
	int tid;
	///user socket
	int skt;
	///user id
	int id;
	///username
	char* username;
	///message frame buffer
	void* frames_buffer;
} UserNode;

///the struct of message 
typedef struct _Msg
{
	UserNode user;
	Frame frame;
} Msg;

#define MSG_LEN (sizeof(Msg))

/// ichat user id
typedef unsigned int uid;

#endif

