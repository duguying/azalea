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

///long message
char full_message[10000];
///short message
char short_message[ID_LEN];

int parse_init(void)
{
	return 0;
}

char* varify_user(char* msg)
{
	memset(short_message, 0, sizeof(char)*ID_LEN);
	strncpy(short_message, msg+1, ID_LEN);
	return short_message;
}
