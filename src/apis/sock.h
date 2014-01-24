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

#include "ichat.h"
#if defined linux
 	#include <sys/socket.h>
	#include <netinet/in.h>
	#include <arpa/inet.h>
	typedef int SOCKET_ID;
	#define PROTO_TCP 0
	#define PROTO_UDP 0
#endif
#if defined _WIN32
	#include "windows.h"
	#include "winsock2.h"
 	typedef unsigned int SOCKET_ID;
 	#define PROTO_TCP 6
 	#define PROTO_UDP 17
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
 * @brief create a socket
 * @details [long description]
 * 
 * @param af address family
 * @param type socket type: 
 *             SOCK_STREAM(if linux, it means tcp),
 *             SOCK_DGRAM(if linux, it means udp),
 *             SOCK_RAW,etc
 * @param protocol trasfer protocol: PROTO_TCP,PROTO_UDP. 
 *                 if in linux is 0
 *  
 * @return socket id
 */
SOCKET_ID
sock_client(
	///address family
	int af,
	///socket type: SOCK_STREAM,SOCK_DGRAM,SOCK_RAW,etc
	int type,
	///trasfer protocol: PROTO_TCP,PROTO_UDP
	int protocol
	);
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

SOCKET_ID 
sock_accept(
	SOCKET_ID skt_id,
	struct sockaddr* client_addr,
	size_t* len
	);

#endif