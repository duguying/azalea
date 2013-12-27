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
	stk->index=(Node**)malloc(sizeof(void*));
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
void extern stack_push(Stack* stk,Node* elem){
	///temp node
	Node* ct;

	stk->index=(Node**)realloc(stk->index,sizeof(Node*)*(stk->size+1));
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
 * @brief pop the top element of stack
 * @details [long description]
 * 
 * @param stk [description]
 */
void stack_pop(Stack* stk){
	if(stk->size<=0){
		return;
	}
	Node* next=stk->top->next;
	free(stk->top);
	if (NULL!=next)
	{
		next->prev=NULL;
	}
	stk->top=next;
	stk->size--;
	stk->index=(Node**)realloc(stk->index,sizeof(void*)*stk->size);
}

/**
 * @brief get the stack node by the index is reverse order(索引倒序)
 * @details [long description]
 * 
 * @param stk [description]
 * @param i [description]
 * @return [description]
 */
Node* stack_get(Stack* stk,int i){
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
void stack_set(Stack* stk,int i,Node* node){
	Node* old_node;
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
	Node* psn=stack->top;
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
	Node* psn=stack->index[0];
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