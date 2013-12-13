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
#include <string.h>
#include "../src/config/config.h"

int main(void)
{
	conf* c=NULL;
	conf configuration;
	int line_length=0;
	c=config_init("./config.ini",&configuration);
	// printf("%d\n", c->size);
	if(c==0){
		printf("config file is not exist!\n");
		return 0;
	}
	config_remove_comment(c);
	config_strip(c);
	printf("content is:\n %s\n\n", c->content);

	line_length=config_current_line(c);

	//printf("line_length is: %d\n", line_length);
	config_destroy(c);
	return 0;
}
