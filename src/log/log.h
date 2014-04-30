/**
 * Azalea Chatting Server
 *
 * Copyright (C) 2013-2015 Rex Lee <duguying2008@gmail.com>
 *
 * This program is free and opensource software; 
 * you can redistribute it and/or modify
 * it under the terms of the GNU General Public License
 */
 
#ifndef _LOG_H
#define _LOG_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include "ds/ds.h"
#include <stdarg.h>
#include <time.h>

/**
 * @brief get current time as string
 * @details get current time as string, 
 * attention! a tring allocaled, user should free it after used
 * 
 * @return [description]
 */
char* log_now(void);

/**
 * create a log
 * @param  file file filename
 * @return      log handle
 */
FILE* log_create(const char* file);

/**
 * write log
 * @param  string log message
 * @return        the byte size have written
 */
void log_printf(const char *format,...);

/**
 * close log
 * @return  if success, return 0
 */
int log_close(void);

/**
 * @brief dump the basic node var
 * @details [long description]
 * 
 * @param node the node
 */
void log_node_dump(Node* node);

#endif

