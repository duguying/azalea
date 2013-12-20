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

///element type
enum etype {inte,floate,stringe,doublee};
//			0		1		2		3

///stack type
enum stype {autos,ints,floats,strings,doubles};
//			0		1		2		3		4

///stack node
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

///the stack
struct Stack
{
	///stack type
	stype type;
	///the current stack size
	int size;
	///top of the stack
	StackNode* top;
	///the stack index
	StackNode** index;
};

/**
 * @brief initial the stack
 * @details [long description]
 * 
 */
Stack* stack_init(stype type);

/**
 * basic push element into stack
 * @param stk  the stack
 * @param elem the element:stack node
 */
void extern stack_push(Stack* stk,StackNode* elem);

/**
 * push the element(which is int) into stack
 * @param stk   [the stack]
 * @param value [the int element]
 */
int stack_push_int(Stack* stk,int value);

/**
 * @brief push the element(float) into stack
 * @details [long description]
 * 
 * @param stk [description]
 * @param value [description]
 * @return [description]
 */
int stack_push_float(Stack* stk,float value);

/**
 * @brief push the element(double) into stack
 * @details [long description]
 * 
 * @param stk [description]
 * @param value [description]
 * @return [description]
 */
int stack_push_double(Stack* stk,double value);

/**
 * @brief push the element(string:char*) into stack
 * @details [long description]
 * 
 * @param stk [description]
 * @param value [description]
 * @return [description]
 */
int stack_push_string(Stack* stk,const char* value);

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
StackNode* stack_get(Stack* stk,int i);

/**
 * @brief set the node by index
 * @details [long description]
 * 
 * @param stk sokect
 * @param i index
 * @param node the node
 * @return [description]
 */
void stack_set(Stack* stk,int i,StackNode* node);

/**
 * @brief create a int stack node
 * @details [long description]
 * 
 * @param value [description]
 * @return [description]
 */
StackNode* stack_node_int(int value);

/**
 * @brief create a string stack node
 * @details [long description]
 * 
 * @param value [description]
 * @return [description]
 */
StackNode* stack_node_float(float value);

/**
 * @brief create a double stack node
 * @details [long description]
 * 
 * @param value [description]
 * @return [description]
 */
StackNode* stack_node_double(double value);

/**
 * @brief create a string stack node
 * @details [long description]
 * 
 * @param value [description]
 * @return [description]
 */
StackNode* stack_node_string(const char* value);

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