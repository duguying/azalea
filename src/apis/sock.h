/**
 * Azalea Chatting Server
 *
 * Copyright (C) 2013-2015 Rex Lee <duguying2008@gmail.com>
 *
 * This program is free and opensource software; 
 * you can redistribute it and/or modify
 * it under the terms of the GNU General Public License
 */

#ifndef _SOCK_H_
#define _SOCK_H_

#include "apis.h"

#if defined _WIN32
	#include "winsock2.h"
	#include "windows.h"
	#include "WS2tcpip.h"
 	typedef unsigned int SOCKET_ID;
 	#define PROTO_TCP 6
 	#define PROTO_UDP 17
#else
 	#include <sys/socket.h>
	#include <netinet/in.h>
	#include <arpa/inet.h>
	typedef int SOCKET_ID;
	#define PROTO_TCP 0
	#define PROTO_UDP 0
#endif

/**
 * set socket address with ip and port
 * @param address the pointer of socket address
 * @param ip      string of ip, NULL for server
 * @param port    port
 */
void 
sock_set_address(
	/// pointer of socket address
	struct sockaddr_in* address, 
	/// ip, NULL for server
	const char* ip, 
	/// port
	int port
	);

/**
 * @brief create a socket for server and binding address for it
 * 
 * @param servaddr server binding address
 *  
 * @return socket id
 */
SOCKET_ID
sock_server(struct sockaddr_in* servaddr);

/**
 * @brief server start listenning
 *
 * @param sid the address binded server socket
 */
int 
sock_listen(SOCKET_ID sid);

/**
 * @brief server accept connection from client
 *
 * @return the client socket id
 */
SOCKET_ID 
sock_accept(
	SOCKET_ID skt_id,
	struct sockaddr* client_addr,
	size_t* len
	);

/**
 * @brief create socket for client
 */
SOCKET_ID
sock_client();

/**
 * @brief socket connect
 * @details [long description]
 * 
 * @param skt_id socket id
 * @param addr socket address
 * @param len length
 */
int
sock_connect(
	SOCKET_ID skt_id,
	struct sockaddr* addr,
	size_t len
	);

#endif
