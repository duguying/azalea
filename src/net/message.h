/**
 * Azalea Chatting Server
 *
 * Copyright (C) 2013-2015 Rex Lee <duguying2008@gmail.com>
 *
 * This program is free and opensource software; 
 * you can redistribute it and/or modify
 * it under the terms of the GNU General Public License
 */

#ifndef _MESSAGE_H_
#define _MESSAGE_H_ 

#include "ichat.h"
#include "ds/stack.h"

///buffer length
#define BUF_LEN 1000 

///the struct of message 
typedef struct Msg
{
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

/// the frame
typedef struct Frame
{
	/// current frame
	unsigned int cf;//4 char
	/// total frame
	unsigned int tf;//4 char
	/// frame content
	char content[FRAME_LEN];
} Frame;

/// frame buffer
Frame FRAME_BUFFER;

/**
 * 调制
 * @param  string [description]
 * @return        [description]
 */
Frame* msg_modulate(char* string);

/**
 * 解调
 * @param  frame [description]
 * @return       [description]
 */
char* msg_demodulate(Frame* frames);

/**
 * push message into message buffer
 * @param  frame_pointer frame buffer
 * @param  frame         single message frame
 * @return               message string
 */
char* msg_frame_buffer_push(Frame** frame_pointer, Frame* frame);


#endif