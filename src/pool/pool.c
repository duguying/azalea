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
void pool_init(void){
	pool=ht_init(POOL_MAX);
}

char* pool_create_index(int tid, int skt){
	return (void*)0;
}

/**
 * save the user into pool
 * @param  index [description]
 * @param  tid   [description]
 * @param  skt   [description]
 * @return       [description]
 */
int pool_connect(const char* index, UserNode* user){
	ht_insert(pool, index, create_node_struct(user));
	printf("\033[0;33m\"%s\" has saved in pool,thread id is %d, sock id is %d\033[0m\n", 
		index, user->tid, user->skt);
	ht_print(pool);
	return 0; // TODO
}

/**
 * @brief get user information from pool
 * @details [long description]
 * 
 * @param index [description]
 * @return get failed -1,others sktid
 */
int pool_get(const char* index){
	Node* tmp=ht_lookup(pool, index);
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
 * @param index [description]
 * @return 0 when success, 1 when failed
 */
int pool_disconnect(const char* index){
	Node* tmp=ht_lookup(pool, index);
	if (tmp)
	{
		ht_remove(pool, index);
		return 0;
	}
	
	return 1;
}

int pool_release(void){
	ht_destroy(pool);
	return 0; // TODO
}
