#include "file.h"

File* file_open(const char* filename){
	File* file=(File*)malloc(sizeof(File));
	memset(file,0,sizeof(File));
	file->filename=filename;
	
	return (void*)NULL;
}

char* file_read(File file){
	return (char*)NULL;
}

int file_write(File file, char* content){
	return 0;
}

int file_close(File file){
	return 0;
}
