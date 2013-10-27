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
	int conf;
	conf=config_init("./ichat.conf");

	return 0;
}
