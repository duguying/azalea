/**
 * Azalea Chatting Server
 *
 * Copyright (C) 2013-2015 Rex Lee <duguying2008@gmail.com>
 *
 * This program is free and opensource software; 
 * you can redistribute it and/or modify
 * it under the terms of the GNU General Public License
 */

#include "args.h"

char CMD[4][10] = {"", "START", "STOP", "RESTART"};

void to_upper_string(char str[]){
	int i=0;
	int len = strlen(str);

	for (i = 0; i < len; ++i)
	{
		if (str[i]>='a' && str[i]<='z')
		{
			str[i]=str[i]-('a'-'A');
		}
	}
}

int arg_parser(int argc, char** argv){
	char command[10];

	memset(command, 0, 10);

	if (argc == 1)
	{
		return 0;
	}else if (argc > 1)
	{
		strncpy(command, argv[1], 10);
		to_upper_string(command);

		if(!strcmp(CMD[1], command)){
			return 1;
		}else if (!strcmp(CMD[2], command))
		{
			return 2;
		}else if (!strcmp(CMD[3], command))
		{
			return 3;
		}else{
			return 0;
		}
	}else{
		return -1;
	}
	
}

