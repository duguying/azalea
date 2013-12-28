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
	Stack* test_stack;

	int i=0;

	for(i=0;i<1000;i++){
		test_stack=stack_init(autos);
		stack_push(test_stack,create_node_int(12));
		stack_push(test_stack,create_node_int(3));
		stack_push(test_stack,create_node_int(41));
		stack_push(test_stack,create_node_int(5));
		stack_push(test_stack,create_node_int(9));
		stack_push(test_stack,create_node_string("hello world!"));
		stack_push(test_stack,create_node_float(12.23));
		stack_push(test_stack,create_node_double(12.2345));
		stack_pop(test_stack);
		stack_pop(test_stack);

		// stack_print(test_stack);
		// stack_reverse_print(test_stack);

		stack_destroy(test_stack);
	}
	



	return 0;
}