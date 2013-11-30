/**
 * Azalea Chatting Server
 *
 * Copyright (C) 2013-2015 Rex Lee <duguying2008@gmail.com>
 *
 * This program is free and opensource software; 
 * you can redistribute it and/or modify
 * it under the terms of the GNU General Public License
 */

#include <stdio.h>
#include <stdlib.h>

#ifndef _STACK_H_
#define _STACK_H_

typedef struct StackNode StsckNode;
typedef struct Stack Stack;

struct StackNode
{
  int value;
  Stack* next;
  Stack* prev;
};

struct Stack
{
	int size;
  Stack* top;
};

/**
 * @brief initial the stack
 * @details [long description]
 * 
 */
void stack_init();

#endif