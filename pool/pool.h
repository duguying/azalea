/// @file pool.h
/// @brief Connection Pool
/// @author Rex Lee duguying2008@gmail.com
/// @version 0.01
/// @date 2013-10-19
#include <stdio.h>
#include <stdlib.h>

typedef struct UserNode{
	int skt;
	char* username;
	int id;
} UserNode;

#define POOL_MAX 10000
#define DB_ON 0 //if 1 database on, 0 off



