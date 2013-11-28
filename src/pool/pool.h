/**
 * Azalea Chatting Server
 *
 * Copyright (C) 2013-2015 Rex Lee <duguying2008@gmail.com>
 *
 * This program is free and opensource software; 
 * you can redistribute it and/or modify
 * it under the terms of the GNU General Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include "../ds/hashtable.h"

typedef struct UserNode
{
	int skt;
	char* username;
	int id;
} UserNode;

typedef HashTable Pool;



#define POOL_MAX 10000
#define DB_ON 0 //if 1 database on, 0 off

/**
 * @brief initial pool
 * @details [long description]
 * 
 * @return pointer of pool
 */
HashTable* pool_init(void);

/**
 * @brief save the user into pool
 * @details [long description]
 * 
 * @param username [description]
 * @param skt [description]
 * @return [description]
 */
int pool_save(const char* username, int skt);

/**
 * @brief get user information from pool
 * @details [long description]
 * 
 * @param username [description]
 * @return [description]
 */
int pool_get(const char* username);

/**
 * @brief disconnect from pool
 * @details [long description]
 * 
 * @param username [description]
 * @return 0 when success, 1 when failed
 */
int pool_discon(const char* username);