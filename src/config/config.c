/**
 * Azalea Chatting Server
 *
 * Copyright (C) 2013-2015 Rex Lee <duguying2008@gmail.com>
 *
 * This program is free and opensource software; 
 * you can redistribute it and/or modify
 * it under the terms of the GNU General Public License
 */

#include "config.h"

/**
 * @brief config initial
 * @details this function not alloc memory for conf* config
 * 
 * @param config_file [description]
 * @return config file handle
 */
conf* 
config_init(const char* config_file){
	struct stat buf;
	conf* config=NULL;
	
	config=(conf*)malloc(sizeof(conf));
	if (NULL==config)
	{
		printf("alloc memory failed!.\n");
		return NULL;
	}
	memset(config,0,sizeof(conf));
	memset(&buf,0,sizeof(struct stat));
	stat(config_file,&buf);
	config->size=buf.st_size;
	config->config_handle=open(config_file, O_RDONLY);
	if (config->config_handle<0)
	{
		printf("open config file failed: %d\n", config->config_handle);
		free(config);
		return (void*)0;
	}
	config->content=(char*)malloc(buf.st_size*sizeof(char));
	config->origin_content=(char*)malloc(buf.st_size*sizeof(char));
	read(config->config_handle,config->origin_content,buf.st_size);
	strncpy(config->content,config->origin_content,buf.st_size*sizeof(char));
	config->vernier=0;
	return config;
}

char* 
config_get(int config_handle, const char* key){
	char* rst=0;
	return rst;
}

/**
 * @brief remove the comment of config file
 * @details remove the comment of config file, the comment is begin with char #
 * 
 * @param config the struct pointer of config
 * @return the struct pointer of config, but carefully if you want to assignment
 */
void* 
config_remove_comment(conf* config){
	int i=0,j=0,tag=0,length=0;
	char* final=NULL;
	if(config==NULL){return (void*)IERROR;}
	char* tmp=(char*)malloc(sizeof(char)*config->size);
	memset(tmp,0,sizeof(char)*config->size);
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
	final=(char*)malloc((length+1)*sizeof(char));
	memset(final,0,sizeof(char)*(length+1));
	strncpy(final,tmp,length);
	free(tmp);
	tmp=NULL;
	free(config->content);
	config->content=final;
	config->size=length;
	config->vernier=0;//the parsing have not start, vernier in 0
	return config;
}

/**
 * @brief remove the empty chars
 * @details [long description]
 * 
 * @param config config the struct pointer of config
 * @return [description]
 */
void* 
config_strip(conf* config){
	int i=0,j=0;
	char* final=NULL;
	char* tmp=(char*)malloc(sizeof(char)*config->size);

	memset(tmp,0,sizeof(char)*config->size);
	for (i = 0; i < config->size; ++i)
	{
		if (i==0)
		{
			tmp[j]=*(config->content+i);
			j++;
		}

		if ('\n'==*(config->content+i)||' '==*(config->content+i))
		{
			if (*(config->content+i)!=tmp[j-1])
			{
				tmp[j]=*(config->content+i);
				j++;
			}
		}else{
			if ('\r'!=*(config->content+i))
			{
				tmp[j]=*(config->content+i);
				j++;
			}
		}
	}
	config->size=strlen(tmp)+1;//leave a char for '\0'
	final=(char*)malloc(sizeof(char)*config->size);
	memset(final,0,sizeof(char)*config->size);
	strncpy(final,tmp,config->size);
	free(tmp);
	tmp=NULL;
	free(config->content);
	config->content=final;
	return config;
}

/**
 * @brief get current line of config, and move the vernier
 * @details get current line of config, and move the vernier
 * 
 * @param config config struct
 * @return the string of current line
 */
int 
config_current_line(conf* config){
	int line_length=0;
	int vernier_point=config->vernier;
	while('\n'!=*(config->content+vernier_point)){
		line_length++;
		printf("c%d : %c\n", vernier_point, *(config->content+vernier_point));
		vernier_point++;
	};
	config->vernier=line_length;
	return vernier_point;
}

/**
 * @brief equation expression parse
 * @details [long description]
 * 
 * @param config [description]
 * @return [description]
 */
void* 
config_equation(conf* config){
	;
}

/**
 * @brief destroy the config
 * @details destroy the config struct and free the memory
 * 
 * @param config config struct
 */
void 
config_destroy(conf* config){
	free(config->content);
	free(config->origin_content);
	free(config);
	config=NULL;
}