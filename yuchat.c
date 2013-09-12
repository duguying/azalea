#include <stdio.h>

int main(int argc,char **argv){
	printf("hello world!");

	//Block the process
	for(;1;){
		sleep(1);
	}
	return 0;
}
