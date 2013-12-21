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
#include <time.h>

/**
 * @brief get current time as string
 * @details get current time as string, 
 * attention! a tring allocaled, user should free it after used
 * 
 * @return [description]
 */
void log_now(void);

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




