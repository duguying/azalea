/**
 * Azalea Chatting Server
 *
 * Copyright (C) 2013-2015 Rex Lee <duguying2008@gmail.com>
 *
 * This program is free and opensource software; 
 * you can redistribute it and/or modify
 * it under the terms of the GNU General Public License
 */

#include "procmanage.h"

int proc_init(){
	// check socket server of master process
	// 
	// try connect master process
	// if cannot connect
	// 		this process initial as master
	// else can connect
	// 		this process initial as worker and the connection between master/worker create
	// endif
	
	SOCKET_ID client_socket_id;
	int conn_result = -1;

	struct sockaddr_in server_address;
	sock_set_address(&server_address, "127.0.0.1", 7777);
	client_socket_id = sock_client();
	conn_result = sock_connect(client_socket_id, (struct sockaddr*)&server_address);
	if (conn_result == -1)
	{
		SOCKET_ID server_sock;
		TID listen_tid;

		printf("connect failed.\nmaster\n");
		sock_close(client_socket_id);

		// creater master sock listener
		server_sock = sock_server(7777);

		// thread_create(&listen_tid, proc_create_sock_serv, server_sock);


	}else if (conn_result == 0)
	{
		printf("connected.\nworker\n");
	}

	return 0;
}

int proc_create_sock_serv(){
	// sock_listen(server_sock);
	return 0;
}

int proc_create_sock_client(){
	return 0;
}

int proc_try_connect_serv(){
	return 0;
}
