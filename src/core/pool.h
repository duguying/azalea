/**
 * Azalea Chatting Server
 *
 * Copyright (C) 2013-2015 Rex Lee <duguying2008@gmail.com>
 *
 * This program is free and opensource software; 
 * you can redistribute it and/or modify
 * it under the terms of the GNU General Public License
 */

#include "common.h"
#include "core/ichat.h"
#include "apis/hashtable.h"
#include "core/message.h"

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
az_exp void pool_init(void);

/**
 * save the user into pool
 * @param  index [description]
 * @param  tid   [description]
 * @param  skt   [description]
 * @return       [description]
 */
az_exp int pool_connect(const char* index, UserNode* user);

/**
 * @brief get user information from pool
 * @details [long description]
 * 
 * @param index [description]
 * @return get failed -1,others sktid
 */
az_exp int pool_get(const char* index);

/**
 * @brief disconnect from pool
 * @details [long description]
 * 
 * @param index [description]
 * @return 0 when success, 1 when failed
 */
az_exp int pool_disconnect(const char* index);

az_exp int pool_release(void);
