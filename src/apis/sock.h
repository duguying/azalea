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
az_exp void 
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
 * @param port server port
 *  
 * @return socket id
 */
az_exp SOCKET_ID
sock_server(int port);

/**
 * @brief server start listenning
 *
 * @param sid the address binded server socket
 */
az_exp int 
sock_listen(SOCKET_ID sid);

/**
 * @brief server accept connection from client
 *
 * @return the client socket id
 */
az_exp SOCKET_ID 
sock_accept(
	// socket id after connect
	SOCKET_ID skt_id,
	// for store client address
	struct sockaddr* client_addr
	);

/**
 * @brief create socket for client
 */
az_exp SOCKET_ID
sock_client();

/**
 * @brief socket connect request
 * 
 * @param skt_id socket id
 * @param addr socket address
 * @param len length
 */
az_exp int
sock_connect(
	SOCKET_ID skt_id,
	// should convert into (struct sockaddr*) by force
	struct sockaddr* addr
	);

/**
 * close the socket and release resource
 */
az_exp int 
sock_close(SOCKET_ID skt_id);

#endif
