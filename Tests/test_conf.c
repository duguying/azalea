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
	c=config_init("./config.ini",&configuration);
	printf("%d\n", c->size);
	config_remove_comment(c);
	config_strip(c);
	printf("%s\n, length %d\n", c->content, strlen(c->content));
	config_destroy(c);
	return 0;
}
