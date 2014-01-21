/**
 * Azalea Chatting Server
 *
 * Copyright (C) 2013-2015 Rex Lee <duguying2008@gmail.com>
 *
 * This program is free and opensource software; 
 * you can redistribute it and/or modify
 * it under the terms of the GNU General Public License
 */

#include "stdio.h"
#include "stdlib.h"
#include "string.h"

///buffer length
#define BUF_LEN 1000 
 
///the struct of message 
typedef struct Msg{
	///the user socket you send to
	int to;
	///the user id you send to
	int to_id;
	///from user socket
	int from;
	///from user id
	int from_id;
	///message
	char message[BUF_LEN];
} Msg;