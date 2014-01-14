/**
 * Azalea Chatting Server
 *
 * Copyright (C) 2013-2015 Rex Lee <duguying2008@gmail.com>
 *
 * This program is free and opensource software; 
 * you can redistribute it and/or modify
 * it under the terms of the GNU General Public License
 */

#include "ichat.h"
#include "pool.h"


HashTable* pool=NULL;

/**
 * @brief initial pool
 * @details [long description]
 * 
 * @return pointer of pool
 */
HashTable* pool_init(void){
	pool=ht_init(10000);
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
int pool_connect(const char* username, int skt){
	ht_insert(pool, username, create_node_int(skt));
	printf("\033[0;33m%s has saved in pool, sock id is %d\033[0m\n", username, skt);
	// ht_print(pool);
}

/**
 * @brief get user information from pool
 * @details [long description]
 * 
 * @param username [description]
 * @return get failed -1,others sktid
 */
int pool_get(const char* username){
	Node* tmp=ht_lookup(pool, username);
	if (tmp)
	{
		return tmp->int_value;
	}
	printf("%s\n", "Attention! User dose not exits!");
	return -1;
}

/**
 * @brief disconnect from pool
 * @details [long description]
 * 
 * @param username [description]
 * @return 0 when success, 1 when failed
 */
int pool_disconnect(const char* username){
	Node* tmp=ht_lookup(pool, username);
	if (tmp)
	{
		ht_remove(pool, username);
		return 0;
	}
	
	return 1;
}