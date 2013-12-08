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

typedef enum etype etype;
typedef enum stype stype;
typedef struct StackNode StackNode;
typedef struct Stack Stack;

//element type
enum etype {inte,floate,stringe,doublee};
//stack type
enum stype {autos,ints,floats,strings,doubles};

//stack node
struct StackNode
{
	etype type;
	int int_value;
	float float_value;
	char* string_value;
	double double_value;
	StackNode* next;
	StackNode* prev;
};

//the stack
struct Stack
{
	stype type;
	int size;
	StackNode* top;
};

/**
 * @brief initial the stack
 * @details [long description]
 * 
 */
void stack_init(Stack* stk , ...);

/**
 * basic push element into stack
 * @param stk  the stack
 * @param elem the element:stack node
 */
void stack_push(Stack* stk,StackNode* elem);

int stack_push_int(Stack* stk,int value);


#endif