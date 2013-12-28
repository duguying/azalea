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
#include <stdarg.h>
#include <time.h>

///the global logfile handle
static FILE *LOG_FILE;
///time string, it is current time after generate(call function log_now)
static char TIME_NOW[20];

/**
 * @brief generate current time string
 * @details get current time as string, after generate, the time is in TIME_NOW
 * @return the pointer of TIME_NOW
 */
char* log_now(void){
	time_t now;
	struct tm *timenow;

	time(&now);
	timenow = localtime(&now);

	sprintf(TIME_NOW,"%d-%d-%d %d:%d:%d",\
		timenow->tm_year+1900,\
		timenow->tm_mon,\
		timenow->tm_mday,\
		timenow->tm_hour,\
		timenow->tm_min,\
		timenow->tm_sec);

	return TIME_NOW;
}

/**
 * create a log
 * @param  file file filename
 * @return      log handle
 */
FILE* log_create(const char* file)
{

	if ((LOG_FILE = fopen(file, "a+")) == NULL)
    {
        fprintf(stderr, "Cannot open output file.\n");
        return (FILE*)0;
    }

	return LOG_FILE;
}

/**
 * close log
 * @return  if success, return 0
 */
int log_close(void)
{
	return fclose(LOG_FILE);
}

/**
 * @brief log my printf
 * @details [long description]
 * 
 * @param format [description]
 */
void log_printf(const char *format,...)
{
    va_list args,argsb;

    ///generate the time string
    log_now();

 ///if define _SRC_LOG_ print the log on the screen
 #ifdef _SCR_LOG_
	printf("[%s]\n", TIME_NOW);

    va_start(args,format);
    vprintf(format,args);
    va_end(args);
 #endif

	fprintf(LOG_FILE,"[%s]\n",TIME_NOW);

	va_start(argsb,format);
    vfprintf(LOG_FILE,format,argsb);
    va_end(argsb);
    fflush(LOG_FILE);
}

/**
 * @brief dump the basic node var
 * @details [long description]
 * 
 * @param node the node
 */
void log_node_dump(Node* node){
	if(inte==node->type){
		printf("%d", node->int_value);
	}else if(floate==node->type){
		printf("%f", node->float_value);
	}else if(doublee==node->type){
		printf("%lf", node->double_value);
	}else if(stringe==node->type){
		printf("%s", node->string_value);
	}else{
		printf("can not dump the var!");
	}
}

