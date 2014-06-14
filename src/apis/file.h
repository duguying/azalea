/**
 * Azalea Chatting Server
 *
 * Copyright (C) 2013-2015 Rex Lee <duguying2008@gmail.com>
 *
 * This program is free and opensource software; 
 * you can redistribute it and/or modify
 * it under the terms of the GNU General Public License
 */

#ifndef _AZALEA_APIS_FILE_
#define _AZALEA_APIS_FILE_

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "common.h"

typedef struct _File
{
	const char* filename;
	FILE* file_handle;
	unsigned char status;
} File;

/**
 * open file
 * @param  filename file name
 * @return          file
 */
az_exp File* file_open(const char* filename);

/**
 * read file
 * @param  file   file
 * @param  buffer buffer reading to
 * @param  length length prepare for reading
 * @return        length have read
 */
az_exp size_t file_read(File* file, void* buffer, size_t length);

/**
 * write binaray file
 * @param  file    file
 * @param  content content for writting
 * @param  size    length prepare for writting
 * @return         length have written
 */
az_exp size_t file_write_bin(File* file, const void* content, size_t size);

/**
 * write file
 * @param  file    file
 * @param  content content for writting
 * @param  size    length prepare for writting
 * @return         length have written
 */
az_exp size_t file_write(File* file, const char* content);

/**
 * file close
 * @param  file file
 * @return      0 will be ok
 */
az_exp int file_close(File* file);

#endif

