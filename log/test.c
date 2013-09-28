#include <stdio.h>

#ifdef _DEBUG_
#include "log.c"
#endif

int main(void){
	int i,lh;
	lh=log_create("test.log");

	for(i=0;i<10000;i++){
		log("hello world, this is a log!\n", lh);
	}
	//log_close();
	
	for(;1;){sleep();}
}
