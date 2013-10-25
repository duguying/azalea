/// @file pool.c
/// @brief Connection Pool
/// @author Rex Lee duguying2008@gmail.com
/// @version 
/// @date 2013-10-19
#include <stdio.h>
#include <stdlib.h>
#include "pool.h"
#include "hashtable.h"


/// @brief connection pool
UserNode pool[POOL_MAX];

/// @brief pool_init 
///
/// @param arg
///
/// @return 
int pool_init(int arg)
{
	ht_init();
	return 0;
}

int pool_save(const char* username, int skt)
{
	ht_insert(username, skt);
}
