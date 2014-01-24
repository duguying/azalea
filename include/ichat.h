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

#if defined linux
	#ifdef _DMALLOC_
	#include "dmalloc.h"
	#endif
#endif
#if defined _WIN32
#endif


///username and etc name
#define ID_LEN 20
///frame length
#define FRAME_LEN (64-8)
///port
#define PORT 6666 
///Empty Char Fill
#define ECF 0 
///pid file
#define PIDF "pid"
///error status
#define IERROR -1
///ok status
#define IOK 0

typedef enum etype etype;
///element type
enum etype{inte,floate,stringe,doublee,structe};
//			0		1		2		3		4
///basic data struct node
typedef struct Node Node;
///stack node
struct Node
{
	etype type;
	int int_value;
	float float_value;
	char* string_value;
	double double_value;
	void* struct_value;
	Node* next;
	Node* prev;
};



/// ichat user id
typedef unsigned int uid;

#endif