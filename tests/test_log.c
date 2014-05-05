/**
 * Azalea Chatting Server
 *
 * Copyright (C) 2013-2015 Rex Lee <duguying2008@gmail.com>
 *
 * This program is free and opensource software; 
 * you can redistribute it and/or modify
 * it under the terms of the GNU General Public License
 */

#include "core/log.h"

int main(void)
{
	int i=0;
	log_create("test.log");

	for(i=0;i<1000;i++){
		log_printf("hello, i am rex\n");
		log_printf("%s:%d:%f:%lf\n","hello world!",12,12.3,12.56789);
	}

	log_close();
	
	return 0;
}
