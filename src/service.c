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
#include <sys/types.h>

 int main(void){
 	int pid;
 	pid=fork();
 	if (pid<0)
 	{
 		printf("an error occurred!\n");
 	}else if (pid>0)//in father
 	{
 		printf("%s\n", "ichat started");
 		exit(0);//in father
 	}else if(pid==0){
 		execve("./ichat");//in son
 	}
 	return 0;
 }