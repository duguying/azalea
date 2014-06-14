/**
 * Azalea Chatting Server
 *
 * Copyright (C) 2013-2015 Rex Lee <duguying2008@gmail.com>
 *
 * This program is free and opensource software; 
 * you can redistribute it and/or modify
 * it under the terms of the GNU General Public License
 */

#ifndef _CORE_ARGS_H_
#define _CORE_ARGS_H_ 

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "common.h"

// extern char CMD[4][10];

/**
 * parse arguments
 * @param  argc argument number
 * @param  argv argumrnts
 * @return      command id
 */
az_exp int arg_parser(int argc, char** argv);

#endif
