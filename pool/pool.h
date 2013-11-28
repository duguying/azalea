/// @file pool.h
/// @brief Connection Pool
/// @author Rex Lee duguying2008@gmail.com
/// @version 0.01
/// @date 2013-10-19
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
 * initial pool
 * @param  arg [description]
 * @return     [description]
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