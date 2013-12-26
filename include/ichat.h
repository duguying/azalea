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
#include <string.h>
#ifdef _DMALLOC_
#include "dmalloc.h"
#endif

///buffer length
#define BUF_LEN 1000 
///username and etc name
#define ID_LEN 20
///pipe buffer
#define PPB_LEN sizeof(Msg)/sizeof(char) 
///port
#define PORT 6666 
///Empty Char Fill
#define ECF 0 
///Error
#define ERROR -1
///pid file
#define PID "pid"


typedef enum etype etype;
typedef enum ntype ntype;
///element type
enum etype {inte,floate,stringe,doublee};
//			0		1		2		3
///node type
enum ntype {autos,ints,floats,strings,doubles};
//			0		1		2		3		4


///the struct of message 
typedef struct Msg{
	///the user socket you send to
	int to;
	///the user id you send to
	int to_id;
	///from user socket
	int from;
	///from user id
	int from_id;
	///message
	char message[BUF_LEN];
} Msg;

#endif