/// @file pool.c
/// @brief Connection Pool
/// @author Rex Lee duguying2008@gmail.com
/// @version 
/// @date 2013-10-19
#include <stdio.h>
#include <stdlib.h>
#include "pool.h"
#include "hashtable.h"

/// @brief pool_init 
///
/// @param arg
///
/// @return 
int pool_init(int arg){
	return 0;
}


/// @brief pool_conn pool connection
///
/// @param ipp ip and port
/// @param skt socket id
///
/// @return connection id
int* pool_conn(char* ipp, int skt){
	return 0;
}

/// @brief pool_get_skt get the socket id
///
/// @param connect_string connection string, such as 127.0.0.1,1234
///
/// @return socket id
int pool_get_skt(char* connect_string){
	return 0;
}
