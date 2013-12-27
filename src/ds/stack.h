/**
 * Azalea Chatting Server
 *
 * Copyright (C) 2013-2015 Rex Lee <duguying2008@gmail.com>
 *
 * This program is free and opensource software; 
 * you can redistribute it and/or modify
 * it under the terms of the GNU General Public License
 */

#include "ichat.h"
#include "ds.h"

#ifndef _STACK_H_
#define _STACK_H_

///stack
typedef struct Stack Stack;

///the stack
struct Stack
{
	///stack type
	ntype type;
	///the current stack size
	int size;
	///top of the stack
	Node* top;
	///the stack index
	Node** index;
};

/**
 * @brief initial the stack
 * @details [long description]
 * 
 */
Stack* stack_init(ntype type);

/**
 * basic push element into stack
 * @param stk  the stack
 * @param elem the element:stack node
 */
void stack_push(Stack* stk,Node* elem);

/**
 * @brief pop the top element of stack
 * @details [long description]
 * 
 * @param stk [description]
 */
void stack_pop(Stack* stk);

/**
 * @brief get the stack node by the index is reverse order(索引倒序)
 * @details [long description]
 * 
 * @param stk [description]
 * @param i [description]
 * @return [description]
 */
Node* stack_get(Stack* stk,int i);

/**
 * @brief set the node by index
 * @details [long description]
 * 
 * @param stk sokect
 * @param i index
 * @param node the node
 * @return [description]
 */
void stack_set(Stack* stk,int i,Node* node);


Stack* stack_reverse(Stack* stk);

void stack_print(Stack* stack);
void stack_reverse_print(Stack* stack);

/**
 * @brief destroy the stack
 * @details [long description]
 * 
 */
void stack_destroy(Stack* stk);



#endif