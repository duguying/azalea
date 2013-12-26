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
Stack* stack_init(ntype type){
	Stack* stk;
	stk=(Stack*)malloc(sizeof(Stack));
	memset(stk,0,sizeof(Stack));

	stk->size=0;
	stk->top=NULL;
	stk->index=(StackNode**)malloc(sizeof(void*));
	memset(stk->index,0,sizeof(void*));

    if(type<0||type>4){
    	printf("%s\n", "stack type error!\n");
    }

    if (type==ints)
    {
    	stk->type=ints;
    }else if (type==floats)
    {
    	stk->type=floats;
    }else if (type==strings)
    {
    	stk->type=strings;
    }else if (type==doubles)
    {
    	stk->type=doubles;
    }else
    {
    	stk->type=autos;
    }
	return stk;
}

/**
 * basic push element into stack
 * @param stk  the stack
 * @param elem the element:stack node
 */
void extern stack_push(Stack* stk,StackNode* elem){
	///temp node
	StackNode* ct;

	stk->index=(StackNode**)realloc(stk->index,sizeof(StackNode*)*(stk->size+1));
	stk->index[stk->size]=elem;
	
	ct=stk->top;
	
	///set top next node
	elem->next=ct;
	elem->prev=NULL;
	///set this element as top
	stk->top=elem;

	///if the top node hava next, set the prev of next as the top
	if(stk->top->next!=NULL){
		stk->top->next->prev=stk->top;
	}

	///increas the size
	stk->size++;
}

/**
 * push the element(which is int) into stack
 * @param stk   [the stack]
 * @param value [the int element]
 */
int stack_push_int(Stack* stk,int value){
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

/**
 * @brief pop the top element of stack
 * @details [long description]
 * 
 * @param stk [description]
 */
void stack_pop(Stack* stk){
	if(stk->size<=0){
		return;
	}
	StackNode* next=stk->top->next;
	free(stk->top);
	if (NULL!=next)
	{
		next->prev=NULL;
	}
	stk->top=next;
	stk->size--;
	stk->index=(StackNode**)realloc(stk->index,sizeof(void*)*stk->size);
}

/**
 * @brief get the stack node by the index is reverse order(索引倒序)
 * @details [long description]
 * 
 * @param stk [description]
 * @param i [description]
 * @return [description]
 */
StackNode* stack_get(Stack* stk,int i){
	if(stk->size>=i){
		return stk->index[i];
	}else{
		return NULL;
	}
}

/**
 * @brief set the node by index
 * @details [long description]
 * 
 * @param stk sokect
 * @param i index
 * @param node the node
 * @return [description]
 */
void stack_set(Stack* stk,int i,StackNode* node){
	StackNode* old_node;
	if(stk->size>=i){
		old_node=stk->index[i];
		node->next=old_node->next;
		old_node->next->prev=node;
		old_node->prev->next=node;
		node->prev=old_node->prev;
		free(old_node);
		old_node=NULL;
		stk->index[i]=node;
	}
}

/**
 * @brief create a int stack node
 * @details [long description]
 * 
 * @param value [description]
 * @return [description]
 */
StackNode* stack_node_int(int value){
	StackNode* sn=(StackNode*)malloc(sizeof(StackNode));
	sn->type=inte;
	sn->int_value=value;
	return sn;
}

/**
 * @brief create a string stack node
 * @details [long description]
 * 
 * @param value [description]
 * @return [description]
 */
StackNode* stack_node_float(float value){
	StackNode* sn=(StackNode*)malloc(sizeof(StackNode));
	sn->type=floate;
	sn->float_value=value;
	return sn;
}

/**
 * @brief create a double stack node
 * @details [long description]
 * 
 * @param value [description]
 * @return [description]
 */
StackNode* stack_node_double(double value){
	StackNode* sn=(StackNode*)malloc(sizeof(StackNode));
	sn->type=doublee;
	sn->double_value=value;
	return sn;
}

/**
 * @brief create a string stack node
 * @details [long description]
 * 
 * @param value [description]
 * @return [description]
 */
StackNode* stack_node_string(const char* value){
	StackNode* sn=(StackNode*)malloc(sizeof(StackNode));
	sn->type=stringe;
	sn->string_value=(char*)value;
	return sn;
}

/**
 * @brief reverse the stack
 * @details [long description]
 * 
 * @param stk [description]
 * @return [description]
 */
Stack* stack_reverse(Stack* stk){
	;
}

/**
 * @brief destroy the stack
 * @details [long description]
 * 
 */
void stack_destroy(Stack* stk){
	int i;
	int node_num=stk->size;
	for (i = 0; i < node_num; ++i)
	{
		stack_pop(stk);
	}
	free(stk->index);
	free(stk);
	stk=NULL;
}

//////////////////////////////////////////////////////////////////

/**
 * @brief print the whole stack
 * @details show the elements of the stack
 * 
 * @param stack the pointer of stack
 */
void stack_print(Stack* stack){
	StackNode* psn=stack->top;
	printf("the stack(size:%d) content is:\n", stack->size);
	printf("%s\n", "-----------------------------");
	printf("%s\n", "TOP");
	while(psn!=NULL){
		if(psn->type==inte){
			printf("[int]   \t\t%d\n",psn->int_value);
		}else if(psn->type==floate){
			printf("[float] \t\t%f\n",psn->float_value);
		}else if(psn->type==stringe){
			printf("[string]\t\t%s\n",psn->string_value);
		}else if(psn->type==doublee){
			printf("[double]\t\t%lf\n",psn->double_value);
		}
		psn=psn->next;
	}
	printf("%s\n", "BOTTOM");
	printf("%s\n", "-----------------------------");
}

void stack_reverse_print(Stack* stack){
	StackNode* psn=stack->index[0];
	printf("the stack(size:%d) content is:\n", stack->size);
	printf("%s\n", "-----------------------------");
	printf("%s\n", "BUTTOM");
	while(psn!=NULL){
		if(psn->type==inte){
			printf("[int]   \t\t%d\n",psn->int_value);
		}else if(psn->type==floate){
			printf("[float] \t\t%f\n",psn->float_value);
		}else if(psn->type==stringe){
			printf("[string]\t\t%s\n",psn->string_value);
		}else if(psn->type==doublee){
			printf("[double]\t\t%lf\n",psn->double_value);
		}
		psn=psn->prev;
	}
	printf("%s\n", "TOP");
	printf("%s\n", "-----------------------------");
}