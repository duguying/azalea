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
#include "log.c"

int main(void)
{
	int i,lh;
	lh=log_create("test.log");

	for(i=0;i<10000;i++){
		logw("hello world, this is a log!\n", lh);
	}
	//log_close();
	
	//for(;1;){sleep();}
}
