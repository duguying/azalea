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
#include "../src/ds/stack.h"

int main(void){
	Stack* test_stack,*test_pressure;

	int i=0;
	StackNode* tpn;//temp node
	StackNode* tpn2;

	test_stack=stack_init(autos);
	stack_push_int(test_stack,12);
	stack_push_int(test_stack,3);
	stack_push_int(test_stack,41);
	stack_push_int(test_stack,5);
	stack_push_int(test_stack,9);
	stack_push_string(test_stack,"hello world!");
	stack_push_float(test_stack,12.23);
	stack_push_double(test_stack,12.2345);

	// stack_print(&test_stack);

	// stack_pop(&test_stack);
	// stack_pop(&test_stack);
	// stack_pop(&test_stack);

	tpn2=stack_node_string("this is a test");
	// stack_set(test_stack, 2, tpn2);

	// stack_print(&test_stack);

	// printf("get nodes by index:\n");
	// for(i=0;i<test_stack.size;i++){
	// 	tpn=test_stack.index[i];
	// 	if(tpn->type==inte){
	// 		printf("[int]   \t\t%d\n",tpn->int_value);
	// 	}else if(tpn->type==floate){
	// 		printf("[float] \t\t%f\n",tpn->float_value);
	// 	}else if(tpn->type==stringe){
	// 		printf("[string]\t\t%s\n",tpn->string_value);
	// 	}else if(tpn->type==doublee){
	// 		printf("[double]\t\t%lf\n",tpn->double_value);
	// 	}
	// }

	// stack_destroy(test_stack);
	// printf("%s\n", "After Destroy:");
	// stack_print(test_stack);

	// printf("pressure test 1 ...\n");

	// int j;
	// for (j = 0; j < 100000000; ++j)
	// {
	// 	stack_push_int(test_stack,j);
	// 	stack_pop(test_stack);
	// }

	// printf("pressure test 2 ...\n");

	// int j;
	// for (j = 0; j < 100000000; ++j)
	// {
	// 	test_pressure=stack_init(inte);
	// 	stack_push_int(test_pressure,j);
	// 	stack_destroy(test_pressure);
	// }

	// stack_pop(test_stack);
	// stack_pop(test_stack);

	// stack_print(test_stack);
	// stack_reverse_print(test_stack);
	// stack_destroy(test_stack);



	return 0;
}