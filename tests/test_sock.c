/**
 * Azalea Chatting Server
 *
 * Copyright (C) 2013-2015 Rex Lee <duguying2008@gmail.com>
 *
 * This program is free and opensource software; 
 * you can redistribute it and/or modify
 * it under the terms of the GNU General Public License
 */

#include "apis/sock.h"

int main(void){
	struct sockaddr_in server_address;
	struct sockaddr_in client_address_you_get;
	SOCKET_ID server_socket_id = 0;
	SOCKET_ID server_after_connect_socket_id = 0;
	SOCKET_ID client_socket_id = 0;

	// create server address for client
	sock_set_address(&server_address, "127.0.0.1", 7777);
	// create server socket
	server_socket_id = sock_server(7777);
	// start server listen
	sock_listen(server_socket_id);
	
	// create client socket
	client_socket_id = sock_client();
	// send connet request to server from client
	sock_connect(client_socket_id, (struct sockaddr*)&server_address);

	// server accept connection request
	sock_accept(server_after_connect_socket_id, (struct sockaddr*)&client_address_you_get);
	
	printf("hello socket...\n");

	return 0;
}