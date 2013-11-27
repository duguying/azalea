/**
 * @file pool.c
 * @brief Connection Pool
 * @author Rex Lee duguying2008@gmail.com
 * @version 
 * @date 2013-10-19
 */
#include <stdio.h>
#include <stdlib.h>
// #include "../ds/hashtable.h"
#include "pool.h"


HashTable* pool=NULL;

/**
 * initial pool
 * @param  arg [description]
 * @return     [description]
 */
HashTable* pool_init(void){
	
	pool=(HashTable*)malloc(sizeof(HashTable));
	ht_init(pool);
	return pool;
}

/**
 * @brief save the user into pool
 * @details [long description]
 * 
 * @param username [description]
 * @param skt [description]
 * @return [description]
 */
int pool_save(const char* username, int skt){
	ht_insert(pool, username, skt);
	printf("\033[0;33m%s has saved in pool, sock id is %d\033[0m\n", username, skt);
}

/**
 * @brief get user information from pool
 * @details [long description]
 * 
 * @param username [description]
 * @return [description]
 */
int pool_get(const char* username){
	HashNode* tmp=ht_lookup(pool, username);
	if (tmp)
	{
		return tmp->nValue;
	}
	printf("%s\n", "Attention! User dose not exits!");
	return -1;
}