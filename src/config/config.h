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
#include <fcntl.h>

typedef struct conf
{
	int size;//size of config file, and this is chars number too
	int config_handle;
	char* content;//file content
	int vernier;//the vernier of current parsing point 当前解析位置游标
} conf;

/**
 * @brief initial config model
 * @details [long description]
 * 
 * @param config_file configuration file
 * @return [description]
 */
conf* config_init(const char* config_file, conf* config);

char* config_get(int config_handle, const char* key);

/**
 * @brief remove the comment of config file
 * @details remove the comment of config file, the comment is begin with char #
 * 
 * @param config the struct pointer of config
 * @return the struct pointer of config, but carefully if you want to assignment
 */
void* config_remove_comment(conf* config);

/**
 * @brief get current line of config, and move the vernier
 * @details get current line of config, and move the vernier
 * 
 * @param config config struct
 * @return the string of current line
 */
int config_current_line(conf* config);