/**
 * Azalea Chatting Server
 *
 * Copyright (C) 2013-2015 Rex Lee <duguying2008@gmail.com>
 *
 * This program is free and opensource software; 
 * you can redistribute it and/or modify
 * it under the terms of the GNU General Public License
 */

#include "common.h"
#include "core/ichat.h"
#include "apis/sock.h"
#include "apis/thread.h"

#define WORKER_NUM 3

az_exp int proc_init();

az_exp int proc_create_sock_serv();

az_exp int proc_create_sock_client();

az_exp int proc_try_connect_serv();
