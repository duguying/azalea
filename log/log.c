#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>


/**
 * create a log
 * @param file filename
 * @return log handle
 */
int log_create(const char* file){
	int lh;
	lh=open(file, O_RDWR|O_CREAT|O_APPEND);
	if(-1==lh){
		printf("create log file error!\n");
	}
	return lh;
}

/**
 * write log
 * @param string log message
 * @param lh log handle
 * @return the byte size have written
 */
int log(const char* string, int lh){
	return write(lh, string, strlen(string));
}

/**
 * close log
 * @param lh log handle
 * @return if success, return 0
 */
int log_close(int lh){
	return close(lh);
}
