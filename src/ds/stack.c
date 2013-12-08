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
#include <stdarg.h>
#include <string.h>
#include "stack.h"

/**
 * @brief initial the stack
 * @details [long description]
 * 
 */
void stack_init(Stack* stk , ...){
	stype stk_type;
	va_list argptr;//the arguments pointer

	stk->size=0;
	stk->top=NULL;

	va_start(argptr, stk);//get the first arg
    stk_type = va_arg(argptr, stype);//next arg

    if (stk_type==ints)
    {
    	stk->type=ints;
    }else if (stk_type==floats)
    {
    	stk->type=floats;
    }else if (stk_type==strings)
    {
    	stk->type=strings;
    }else if (stk_type==doubles)
    {
    	stk->type=doubles;
    }else if (stk_type>doubles||stk_type<=autos)
    {
    	stk->type=autos;
    }
	
}

/**
 * basic push element into stack
 * @param stk  the stack
 * @param elem the element:stack node
 */
void extern stack_push(Stack* stk,StackNode* elem){
	memset(elem,0,sizeof(StackNode));

	if (!stk->top)
	{
		stk->top=elem;
		stk->top->next=NULL;
		stk->top->prev=NULL;
	}else{
		stk->top->next=elem;
		stk->top->next->prev=stk->top->next;
		stk->top=stk->top->next;
	};
}

/**
 * push the element(which is int) into stack
 * @param stk   [the stack]
 * @param value [the int element]
 */
int stack_push_int(Stack* stk,int value){
	if (ints!=stk->type||autos!=stk->type)
	{
		printf("%s\n", "error:the stack type error!");
		return -1;
	}
	StackNode* elem=(StackNode*)malloc(sizeof(StackNode));
	memset(elem,0,sizeof(StackNode));
	elem->type=inte;
	elem->int_value=value;
	stack_push(stk,elem);
}

int stack_push_float(Stack* stk,float value){
	if (floats!=stk->type||autos!=stk->type)
	{
		printf("%s\n", "error:the stack type error!");
		return -1;
	}
	StackNode* elem=(StackNode*)malloc(sizeof(StackNode));
	memset(elem,0,sizeof(StackNode));
	elem->type=floate;
	elem->float_value=value;
	stack_push(stk,elem);
}

int stack_push_double(Stack* stk,double value){
	if (doubles!=stk->type||autos!=stk->type)
	{
		printf("%s\n", "error:the stack type error!");
		return -1;
	}
	StackNode* elem=(StackNode*)malloc(sizeof(StackNode));
	memset(elem,0,sizeof(StackNode));
	elem->type=doublee;
	elem->double_value=value;
	stack_push(stk,elem);
}

int stack_push_string(Stack* stk,const char* value){
	if (strings!=stk->type||autos!=stk->type)
	{
		printf("%s\n", "error:the stack type error!");
		return -1;
	}
	StackNode* elem=(StackNode*)malloc(sizeof(StackNode));
	memset(elem,0,sizeof(StackNode));
	elem->type=stringe;
	elem->string_value=(char*)value;
	stack_push(stk,elem);
}

void stack_pop(){
	;
}

void stack_get(int i){
	;
}

void stack_set(int i){
	;
}