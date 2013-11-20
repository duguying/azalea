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
	read(config->config_handle,config->content,buf.st_size);
	// strncpy(config->content,"hello world!",13);
	return config;
}

char* config_get(int config_handle, const char* key)
{
	char* rst=0;
	return rst;
}

/**
 * @brief remove the comment of config file
 * @details remove the comment of config file, the comment is begin with char #
 * 
 * @param config the struct pointer of config
 * @return the struct pointer of config
 */
conf* remove_comment(conf* config){
	int i=0,j=0,tag=0,length=0;
	char* final=NULL;
	char* tmp=(char*)malloc(sizeof(char)*config->size);
	for (i = 0; i < config->size; ++i)
	{
		if ('#'==*(config->content+i))
		{
			tag=1;
		}else if('\n'==*(config->content+i)){
			tag=0;
			tmp[j]=*(config->content+i);
			j++;
		}else{
			if (tag==0)
			{
				tmp[j]=*(config->content+i);
				j++;
			}else{
			}
		}
	}
	length=strlen(tmp);
	final=(char*)malloc(length*sizeof(char));
	strncpy(final,tmp,length);
	free(tmp);
	free(config->content);
	config->content=final;
	return config;
}

void config_destroy(conf* config){
	// free(config->content);
	// config->content=NULL;
	printf("%s\n, length %d\n", config->content, strlen(config->content));
}