/**
 * @file parser.c
 * @brief parse the message
 * @author Rex Lee duguying2008@gmail.com
 * @version 0.01
 * @date 2013-10-19
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../ichat.h"

char full_message[BUF_LEN];
char short_message[ID_LEN];

int parse_init(void)
{
	return 0;
}

char* parse_get_username(char* msg)
{
	memset(short_message, 0, sizeof(char)*ID_LEN);
	strncpy(short_message, msg+1, ID_LEN);
	return short_message;
}

int is_username(char* msg)
{
	int is=0;
	return is;
}
