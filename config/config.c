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
#include <sys/stat.h>
#include <string.h>
#include "config.h"

/**
 * @brief config initial
 * @details [long description]
 * 
 * @param config_file [description]
 * @return config file handle
 */
conf* config_init(const char* config_file,conf* config)
{
	memset(config,0,sizeof(conf));
	struct stat buf;
	memset(&buf,0,sizeof(struct stat));
	stat(config_file,&buf);
	config->size=buf.st_size;
	config->config_handle=open(config_file, O_RDONLY);

	config->content=(char*)malloc(buf.st_size*sizeof(char));
	// strncpy(config->content,"hello world!",13);
	return config;
}

char* config_get(int config_handle, const char* key)
{
	char* rst=0;
	return rst;
}

void* remove_comment(){
	;
}

void config_destroy(conf* config){
	free(config->content);
	config->content=NULL;
	// printf("%s\n", config->content);
}