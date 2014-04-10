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


///username and etc name
#define ID_LEN 20
///frame size
#define FRAME_SIZE 64
///frame length
#define FRAME_LEN (FRAME_SIZE-8)
#define MSG_LEN sizeof(Msg)
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
typedef struct _Node Node;
struct _Node
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

/// the frame
typedef struct _Frame
{
	/// current frame
	unsigned int cf;//4 char
	/// total frame
	unsigned int tf;//4 char
	/// frame content
	char content[FRAME_LEN];
} Frame;

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

/// ichat user id
typedef unsigned int uid;

#endif

