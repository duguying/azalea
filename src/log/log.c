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
#include <string.h>

/**
 * @brief initialize the model
 * @details long description
 * 
 * @return description
 */
int initial(void)
{
	printf("Load Log Model success!\n");
	//log_create("test.log");
	return 0;
}

/**
 * @brief log_create create a log
 * @details  
 * 
 * @param file file filename
 * @return log handle
 */
int log_create(const char* file)
{
	int lh;
	lh=open(file, O_RDWR|O_CREAT|O_APPEND);
	if(-1==lh){
		printf("create log file error!\n");
	}
	return lh;
}


/**
 * @brief logw write log
 * @details  
 * 
 * @param string log message
 * @param lh log handle
 * @return the byte size have written
 */
int logw(const char* string, int lh)
{
	return write(lh, string, strlen(string));
}

/**
 * @brief close log
 * @details long description
 * 
 * @param lh log handle
 * @return if success, return 0
 */
int log_close(int lh)
{
	return close(lh);
}
