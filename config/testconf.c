/// @file config.h
/// @brief configuration model head
/// @author Rex Lee duguying2008@gmail.com
/// @version 0.01
/// @date 2013-10-19
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "config.h"

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
