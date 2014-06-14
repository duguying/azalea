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

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include "apis/stack.h"
#include "common.h"

///frame size
#define FRAME_SIZE 64
///frame length
#define FRAME_LEN (FRAME_SIZE-8)

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

/**
 * 调制
 * @param  string [description]
 * @return        [description]
 */
az_exp Frame* msg_modulate(char* string);

/**
 * 解调
 * @param  frame [description]
 * @return       [description]
 */
az_exp char* msg_demodulate(Frame* frames);

/**
 * @brief push message into message buffer
 * @details [long description]
 * 
 * @param frame_stack frame buffer stack
 * @param frame frame you received
 * 
 * @return the message demodulate
 */
az_exp char* msg_frame_buffer_push(Stack* frame_stack, Frame* frame);


#endif
