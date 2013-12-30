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

SOCKET_ID
sock_server(){}

#if defined _WIN32
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
#endif
#if defined linux
SOCKET_ID
sock_client(
	///address family
	int af,
	///socket type: SOCK_STREAM,SOCK_DGRAM,SOCK_RAW,etc
	int type,
	///trasfer protocol: PROTO_TCP,PROTO_UDP
	int protocol
	){
	SOCKET_ID skt_id;
	skt_id=socket(af,type,protocol);
	if(-1==skt_id){
		return IERROR;
	}
	return skt_id;
}
#endif

#if defined _WIN32
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
	){
	if (SOCKET_ERROR==connect(skt_id,addr,len))
	{
		printf("Failed to connect.\n");
		WSACleanup();
		return -1;
	}else{
		return 0;
	}
}
#endif
#if defined linux
int
sock_connect(
	SOCKET_ID skt_id,
	struct sockaddr* addr,
	size_t len
	){
	if (-1==connect(skt_id,addr,len))
	{
		printf("Failed to connect.\n");
		return -1;
	}else{
		return 0;
	}
}
#endif