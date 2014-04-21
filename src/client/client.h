/**
 * Azalea Chatting Server
 *
 * Copyright (C) 2013-2015 Rex Lee <duguying2008@gmail.com>
 *
 * This program is free and opensource software; 
 * you can redistribute it and/or modify
 * it under the terms of the GNU General Public License
 */

#ifndef _AZALEA_CLIENT_CLIENT_
#define _AZALEA_CLIENT_CLIENT_

#if defined _WIN32
	#include "ichat.h"
	#include "apis/sock.h"
	#include "apis/thread.h"
	#include "net/message.h"
	#include <sys/types.h>
	#include <conio.h>
	#define getch()	_getch()
#else
	#include <termios.h>
	#include <unistd.h>
	#include "ichat.h"
	#include "apis/sock.h"
	#include "apis/thread.h"
	#include "net/message.h"
	#include <sys/types.h>
#endif
 
#endif
