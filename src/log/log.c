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
#include <fcntl.h>

//the global logfile handle
static int logh;

/**
 * initialize the model
 * @return  0 for success
 */
int initial(void)
{
	printf("Load Log Model success!\n");
	//log_create("test.log");
	return 0;
}

/**
 * create a log
 * @param  file file filename
 * @return      log handle
 */
int log_create(const char* file)
{
	// int lh;
	logh=open(file, O_RDWR|O_CREAT|O_APPEND);
	if(-1==logh){
		printf("create log file error!\n");
	}
	return logh;
}

/**
 * write log
 * @param  string log message
 * @return        the byte size have written
 */
int log_printf(const char* string)
{
	return write(logh, string, strlen(string));
}

/**
 * close log
 * @return  if success, return 0
 */
int log_close(void)
{
	return close(logh);
}
