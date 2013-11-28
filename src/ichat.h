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

#define BUF_LEN 1000 //buffer length
#define ID_LEN 20 //username and etc name
#define PPB_LEN sizeof(Msg)/sizeof(char) //pipe buffer
#define PORT 6666 //port
#define ECF 0 //Empty Char Fill
// #define QUIET 1
// #define iprintf(args) ((QUIET)?0:(printf(args)))

typedef struct Msg{
	int to;
	int to_id;
	int from;// from user skt
	int from_id;
	char message[BUF_LEN];
} Msg;
