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
#include "ds/hashtable.h"

///user node in the connection pool
typedef struct UserNode
{
	///user socket
	int skt;
	///username
	char* username;
	///user id
	int id;
} UserNode;

///connection pool
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
int pool_connect(const char* username, int skt);

/**
 * @brief disconnect from pool
 * @details [long description]
 * 
 * @param username [description]
 * @return 0 when success, 1 when failed
 */
int pool_disconnect(const char* username);

/**
 * @brief get user information from pool
 * @details [long description]
 * 
 * @param username [description]
 * @return get failed -1,others sktid
 */
int pool_get(const char* username);

int pool_release(void);