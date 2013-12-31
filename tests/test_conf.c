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
#include "config/config.h"

int main(void)
{
	conf* configuration;
	int line_length=0;
	configuration=config_init("./config.ini");
	// printf("%d\n", configuration->size);
	if(configuration==0){
		printf("config file is not exist!\n");
		return 0;
	}
	config_remove_comment(configuration);
	config_strip(configuration);
	printf("content is:\n %s\n\n", configuration->content);

	line_length=config_current_line(configuration);

	//printf("line_length is: %d\n", line_length);
	config_destroy(configuration);
	return 0;
}
