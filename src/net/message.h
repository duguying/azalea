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
char* msg_frame_buffer_push(Stack* frame_stack, Frame* frame);


#endif