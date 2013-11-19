/**
 * @file config.c
 * @brief configuration model
 * @author Rex Lee duguying2008@gmail.com
 * @version 0.01
 * @date 2013-10-19
 */
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

/**
 * @brief config initial
 * @details [long description]
 * 
 * @param config_file [description]
 * @return [description]
 */
int config_init(const char* config_file)
{
	return open(config_file, O_RDONLY);
}

char* config_get(int conf, const char* key)
{
	char* rst=0;
	return rst;
}
