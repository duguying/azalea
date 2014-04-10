/**
 * Azalea Chatting Server
 *
 * Copyright (C) 2013-2015 Rex Lee <duguying2008@gmail.com>
 *
 * This program is free and opensource software; 
 * you can redistribute it and/or modify
 * it under the terms of the GNU General Public License
 */

#include "ichat.h"
#include "ds/hashtable.h"
#include "apis/file.h"

/**
 * @brief config struct
 * @details config struct, it is the contener of the configuration
 */
typedef struct conf
{
	///size of config file, and this is chars number too
	int size;
	///configure file handle
	File* config_handle;
	///file content
	char* content;
	///original file content
	char* origin_content;
	///the vernier of current parsing point 当前解析位置游标
	int vernier;
	///the config contener
	HashTable config;
} conf;

/**
 * @brief initial config model
 * @details [long description]
 * 
 * @param config_file configuration file
 * @return the pointer of conf struct
 */
conf* config_init(const char* config_file);

char* config_get(int config_handle, const char* key);

/**
 * @brief remove the comment of config file
 * @details remove the comment of config file, the comment is begin with char #
 * 
 * @param config the struct pointer of config
 * @return the struct pointer of config, but carefully if you want to assignment
 */
void* 
config_remove_comment(conf* config);

/**
 * @brief remove the empty chars
 * @details [long description]
 * 
 * @param config config the struct pointer of config
 * @return [description]
 */
void* 
config_strip(conf* config);

/**
 * @brief get current line of config, and move the vernier
 * @details get current line of config, and move the vernier
 * 
 * @param config config struct
 * @return the string of current line
 */
int 
config_current_line(conf* config);

/**
 * @brief equation expression parse
 * @details [long description]
 * 
 * @param config [description]
 * @return [description]
 */
void* 
config_equation(conf* config);

/**
 * @brief destroy the config
 * @details destroy the config struct and free the memory
 * 
 * @param config config struct
 */
void 
config_destroy(conf* config);