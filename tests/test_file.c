#include "apis/file.h"


int main(int argc, char const *argv[])
{
	File* file;
	size_t len1,len2;
	char buffer[13];
	
	file=file_open("test_rex.txt");
	len1=file_write(file,"hello world!");
	if (len1<0)
	{
		printf("write失败\n");
		return 0;
	}
	memset(buffer,0,13);
	len2=file_read(file,buffer,11);
	if (len2<0)
	{
		printf("read失败\n");
		return 0;
	}else{
		printf("buffer: %s\n", buffer);
	}
	file_close(file);

	return 0;
}



