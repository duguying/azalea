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
#include "apis/sock.h"


int main(void){
	// int skt;
	sock_client(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	return 0;
}