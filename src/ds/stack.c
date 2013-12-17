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
#include <stdarg.h>
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

    if(stk_type<0||stk_type>4){
    	printf("%s\n", "stack type error!\n");
    	// return -1;
    }

    // printf("%d\n", stk_type);//0

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
    }else
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
	///temp node
	StackNode* ct;
	ct=stk->top;
	///set top next node
	elem->next=ct;
	///set this element as top
	stk->top=elem;
}

/**
 * push the element(which is int) into stack
 * @param stk   [the stack]
 * @param value [the int element]
 */
int stack_push_int(Stack* stk,int value){
	// printf("%d\n", stk->type);
	if (ints!=stk->type&&autos!=stk->type)
	{
		printf("%s\n", "error:the stack type error!need int.");
		return -1;
	}
	StackNode* elem=(StackNode*)malloc(sizeof(StackNode));
	memset(elem,0,sizeof(StackNode));
	elem->type=inte;
	elem->int_value=value;

	stack_push(stk,elem);
}

/**
 * @brief push the element(float) into stack
 * @details [long description]
 * 
 * @param stk [description]
 * @param value [description]
 * @return [description]
 */
int stack_push_float(Stack* stk,float value){
	if (floats!=stk->type&&autos!=stk->type)
	{
		printf("%s\n", "error:the stack type error!need float.");
		return -1;
	}
	StackNode* elem=(StackNode*)malloc(sizeof(StackNode));
	memset(elem,0,sizeof(StackNode));
	elem->type=floate;
	elem->float_value=value;
	// printf("%lf\n", value);
	stack_push(stk,elem);
}

/**
 * @brief push the element(double) into stack
 * @details [long description]
 * 
 * @param stk [description]
 * @param value [description]
 * @return [description]
 */
int stack_push_double(Stack* stk,double value){
	if (doubles!=stk->type&&autos!=stk->type)
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

/**
 * @brief push the element(string:char*) into stack
 * @details [long description]
 * 
 * @param stk [description]
 * @param value [description]
 * @return [description]
 */
int stack_push_string(Stack* stk,const char* value){
	if (strings!=stk->type&&autos!=stk->type)
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

/**
 * @brief print the whole stack
 * @details show the elements of the stack
 * 
 * @param stack the pointer of stack
 */
void stack_print(Stack* stack){
	StackNode* psn=stack->top;
	printf("%s\n", "the stack content is:");
	printf("%s\n", "-----------------------------");
	printf("%s\n", "TOP");
	while(psn!=NULL){
		if(psn->type==inte){
			printf("[int]\t%d\n",psn->int_value);
		}else if(psn->type==floate){
			printf("[float]\t%f\n",psn->float_value);
		}else if(psn->type==stringe){
			printf("[string]\t%s\n",psn->string_value);
		}else if(psn->type==doublee){
			printf("[double]\t%lf\n",psn->double_value);
		}
		psn=psn->next;
	}
	printf("%s\n", "BOTTOM");
}