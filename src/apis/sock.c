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

void 
sock_set_address(
	/// pointer of socket address
	struct sockaddr_in* address, 
	/// ip, NULL for server
	const char* ip, 
	/// port
	int port
	){
	memset(address, 0, sizeof(struct sockaddr_in));
	address->sin_family = AF_INET;

	if (NULL==ip)
	{
		address->sin_addr.s_addr = htonl(INADDR_ANY);
	}else{
		address->sin_addr.s_addr = inet_addr(ip);
	}
	
	address->sin_port = htons(port);
}

/////////////////////////////

#if defined _WIN32

SOCKET_ID
sock_server(int port){
	WSADATA wsaData;
	SOCKET_ID socket_server;
	int iResult;
	struct addrinfo* result = NULL, hints;
	char c_port[8];

	iResult = WSAStartup(MAKEWORD(2,2),&wsaData);
	if (iResult != 0)
	{
		printf("WSAStartup Failed: %d\n", iResult);
		return 1;
	}
	// address
	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_flags = AI_PASSIVE;

	sprintf(c_port, "%d", port);

	// get host address
	iResult = getaddrinfo(
				NULL,	// local host
				c_port,	// port
				&hints,
				&result);

	if (iResult != 0)
	{
		printf("getaddrinfo Failed: %d\n", iResult);
		WSACleanup();
		return 1;
	}

	// create socket
	socket_server = socket(result->ai_family,	result->ai_socktype, result->ai_protocol);

	if (socket_server == INVALID_SOCKET)
	{
		printf("socket Failed: %d\n", WSAGetLastError());
		freeaddrinfo(result);
		WSACleanup();
		return 1;
	}

	// binding 
	iResult = bind(socket_server, result->ai_addr, (int)result->ai_addrlen);
	if (iResult == SOCKET_ERROR)
	{
		printf("binding Failed: %d\n", WSAGetLastError());
		freeaddrinfo(result);
		closesocket(socket_server);
		WSACleanup();
		return 1;
	}

	return socket_server;
}

#else

SOCKET_ID
sock_server(int port){
	int sid=0;
	int bind_result=0;
	struct sockaddr_in servaddr;

	sock_set_address(&servaddr, NULL, port);
	
	sid = socket(AF_INET, SOCK_STREAM, PROTO_TCP);
	if (sid==-1)
	{
		printf("Error at socket create in sock_server().\n");
		return -1;
	}

	bind_result = bind(sid, (struct sockaddr*)&servaddr, sizeof(servaddr));
	if (-1==bind_result)
	{
		printf("Error at socket bind in sock_server().\n");
		return -1;
	}

	return sid;
}

#endif

/////////////////////////////

int sock_listen(SOCKET_ID sid){
	int backlog = 10;
	return listen(sid, backlog);
}

/////////////////////////////

SOCKET_ID 
sock_accept(
	SOCKET_ID skt_id,
	struct sockaddr* client_addr
	){
	size_t len = sizeof(struct sockaddr_in);
	return accept(skt_id,client_addr,(socklen_t*)(&len));
}

/////////////////////////////

#if defined _WIN32

SOCKET_ID
sock_client(){
	WSADATA wsaData;
	int iResult;
	SOCKET_ID skt_id;

	iResult=WSAStartup(MAKEWORD(2,2),&wsaData);
	if(iResult!=NO_ERROR){
		printf("Error at WSAStartup().\n");
		return ERROR;
	}
	skt_id=socket(AF_INET, SOCK_STREAM, PROTO_TCP);
	if (INVALID_SOCKET==skt_id)
	{
		printf("Error at socket().\n");
		WSACleanup();
		return ERROR;
	}
	return skt_id;
}

#else

SOCKET_ID
sock_client(){
	SOCKET_ID skt_id;
	skt_id=socket(AF_INET, SOCK_STREAM, PROTO_TCP);
	if(-1==skt_id){
		return IERROR;
	}
	return skt_id;
}

#endif

/////////////////////////////

#if defined _WIN32

int
sock_connect(
	SOCKET_ID skt_id,
	struct sockaddr* addr
	){
	if (SOCKET_ERROR==connect(skt_id, addr, sizeof(struct sockaddr_in)))
	{
		printf("Failed to connect.\n");
		WSACleanup();
		return -1;
	}else{
		return 0;
	}
}

#else

int
sock_connect(
	SOCKET_ID skt_id,
	struct sockaddr* addr
	){
	if (-1==connect(skt_id, addr, sizeof(struct sockaddr_in)))
	{
		printf("Failed to connect.\n");
		return -1;
	}else{
		return 0;
	}
}

#endif

#if defined _WIN32

int 
sock_close(SOCKET_ID skt_id){
	closesocket(skt_id);
	WSACleanup();
	return 0;
}

#else

int 
sock_close(SOCKET_ID skt_id){
	close(skt_id);
	return 0;
}

#endif
