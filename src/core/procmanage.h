/**
 * Azalea Chatting Server
 *
 * Copyright (C) 2013-2015 Rex Lee <duguying2008@gmail.com>
 *
 * This program is free and opensource software; 
 * you can redistribute it and/or modify
 * it under the terms of the GNU General Public License
 */

#include "core/ichat.h"
#include "apis/sock.h"

int proc_init();

int proc_create_sock_serv();

int proc_create_sock_client();

int proc_try_connect_serv();
