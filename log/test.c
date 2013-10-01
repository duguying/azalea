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
