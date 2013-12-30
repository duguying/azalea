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
#if defined linux
	#ifdef _DMALLOC_
	#include "dmalloc.h"
	#endif
#endif
#if defined _WIN32
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
///pid file
#define PIDF "pid"
///error status
#define IERROR -1
///ok status
#define IOK 0

typedef enum etype etype;
///element type
enum etype{inte,floate,stringe,doublee};
//			0		1		2		3
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
	Node* next;
	Node* prev;
};

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