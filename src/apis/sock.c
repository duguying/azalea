/**
 * Azalea Chatting Server
 *
 * Copyright (C) 2013-2015 Rex Lee <duguying2008@gmail.com>
 *
 * This program is free and opensource software; 
 * you can redistribute it and/or modify
 * it under the terms of the GNU General Public License
 */

#include "sock.h"
#if defined linux
	#include <sys/socket.h>
	#include <netinet/in.h>
	#include <arpa/inet.h>
#endif
#if defined _WIN32
 	#include "winsock2.h"
#endif

SOCKET_ID
sock_server(){}

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
	){
	WSADATA wsaData;
	int iResult;
	SOCKET_ID skt_id;

	iResult=WSAStartup(MAKEWORD(2,2),&wsaData);
	if(iResult!=NO_ERROR){
		printf("Error at WSAStartup().\n");
		return ERROR;
	}
	skt_id=socket(af, type, protocol);
	if (INVALID_SOCKET==skt_id)
	{
		printf("Error at socket().\n");
		WSACleanup();
		return ERROR;
	}
	return skt_id;
}

int
sock_connect(
	// SOCKET_ID skt_id
	){}