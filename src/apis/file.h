#include "stdio.h"
#include "stdlib.h"

typedef struct _File
{
	const char* filename;
	int file_handle;
	unsigned char status;
} File;

File* file_open(const char* filename);

char* file_read(File file);

int file_write(File file, char* content);

int file_close(File file);
