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
#include "ds/stack.h"
#include "apis/file.h"

int main(void){
	char* file = "./Makefile";
	Frame* msg;
	File* fh;
	char content[102400];
	char* str;
	int tf,i;
	// Frame* frames_buffer;
	Stack* stack_buffer;
	
	fh=file_open(file);
	file_read(fh,content,102400);
	// char* content="hello world!";

	msg=msg_modulate(content);
	// str=msg_demodulate(msg);

	stack_buffer=stack_init(structs);

	// printf("string:\n%s\n", str);

	tf=msg[0].tf;
	for (i = 0; i < tf; ++i)
	{
		printf("%d\n", i);
		str=msg_frame_buffer_push(stack_buffer,&msg[i]);
	}
	free(msg);
	printf("%s\n", str);
	free(str);
	free(stack_buffer);
	return 0;
}