/**
 * Azalea Chatting Server
 *
 * Copyright (C) 2013-2015 Rex Lee <duguying2008@gmail.com>
 *
 * This program is free and opensource software; 
 * you can redistribute it and/or modify
 * it under the terms of the GNU General Public License
 */

#include "net/message.h"
#include <fcntl.h>
#include <sys/stat.h>

int main(void){
	char* file = "../Makefile";
	Frame* msg;
	int fh;
	char content[102400];
	char* str;
	
	fh=open(file, O_RDONLY);
	read(fh,content,102400);
	// char* content="hello world!";

	msg=msg_modulate(content);
	str=msg_demodulate(msg);

	printf("string:\n%s\n", str);

	return 0;
}