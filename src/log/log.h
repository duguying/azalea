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

/**
 * initialize the model
 * @return  0 for success
 */
int initial(void);

/**
 * create a log
 * @param  file file filename
 * @return      log handle
 */
int log_create(const char* file);

/**
 * write log
 * @param  string log message
 * @return        the byte size have written
 */
int log_printf(const char* string);

/**
 * close log
 * @return  if success, return 0
 */
int log_close(void);
