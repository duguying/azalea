#include "file.h"

File* file_open(const char* filename){
	File* file;
	FILE* rawfilehdl;

	if((rawfilehdl=fopen(filename,"r"))==NULL){
		return NULL;
	}else{
		fclose(rawfilehdl);
	}
	
	file=(File*)malloc(sizeof(File));
	memset(file,0,sizeof(File));
	file->filename=filename;
	return file;
	
}

size_t file_read(File* file, void* buffer, size_t length){
	size_t len;

	file->file_handle=fopen(file->filename,"r");
	if (file->file_handle<=0)
	{
		printf("open failed!\n");
		return 0;
	}
	len=fread(buffer, length, 1, file->file_handle);
	if (file->file_handle!=NULL)
	{
		fclose(file->file_handle);
		file->file_handle=NULL;
	}

	return len;
}

size_t file_write_bin(File* file, const void* content, size_t size){
	size_t len;

	file->file_handle=fopen(file->filename,"a+");
	if (file->file_handle<=0)
	{
		printf("open failed!\n");
		return 0;
	}
	len=fwrite(content, size, 1, file->file_handle);
	if (file->file_handle!=NULL)
	{
		fclose(file->file_handle);
		file->file_handle=NULL;
	}

	return len;
}

size_t file_write(File* file, const char* content){
	size_t len;

	file->file_handle=fopen(file->filename,"at+");
	if (file->file_handle<=0)
	{
		printf("open failed!\n");
		return 0;
	}
	len=fprintf(file->file_handle, "%s", content);
	if (file->file_handle!=NULL)
	{
		fclose(file->file_handle);
		file->file_handle=NULL;
	}
	

	return len;
}

int file_close(File* file){
	if (file!=NULL)
	{
		free(file);
		file=NULL;
	}
	
	return 0;
}
