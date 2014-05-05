/**
 * Azalea Chatting Server
 *
 * Copyright (C) 2013-2015 Rex Lee <duguying2008@gmail.com>
 *
 * This program is free and opensource software; 
 * you can redistribute it and/or modify
 * it under the terms of the GNU General Public License
 */

// #include "ichat.h"
#include "apis/hashtable.h"
#include "net/message.h"
#include "pool/pool.h"

int main(void){
	UserNode user={
		123,
		456,
		1,
		"test",
		NULL
	};
	// create_node_struct(&user);

	pool_init();
	pool_connect("123456",&user);
	pool_release();
	return 0;
}
