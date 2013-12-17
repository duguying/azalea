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
	Stack test_stack;
	stype st=autos;

	stack_init(&test_stack,st);
	stack_push_int(&test_stack,12);
	stack_push_int(&test_stack,3);
	stack_push_int(&test_stack,41);
	stack_push_int(&test_stack,5);
	stack_push_int(&test_stack,9);
	stack_push_string(&test_stack,"hello world!");
	stack_push_float(&test_stack,12.23);
	stack_push_double(&test_stack,12.2345);

	stack_print(&test_stack);

	return 0;
}