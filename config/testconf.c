/// @file config.h
/// @brief configuration model head
/// @author Rex Lee duguying2008@gmail.com
/// @version 0.01
/// @date 2013-10-19
#include <stdio.h>
#include <stdlib.h>
#include "config.h"

int main(void)
{
	conf* c=NULL;
	conf configuration;
	c=config_init("./config.ini",&configuration);
	printf("%d\n", c->size);
	c=remove_comment(c);
	config_destroy(c);
	return 0;
}
