/// @file test.c
/// @brief log model test
/// @author Rex Lee duguying2008@gmail.com
/// @version 0.01
/// @date 2013-10-19
#include <stdio.h>
#include "log.c"

int main(void){
	int i,lh;
	lh=log_create("test.log");

	for(i=0;i<10000;i++){
		logw("hello world, this is a log!\n", lh);
	}
	//log_close();
	
	//for(;1;){sleep();}
}
