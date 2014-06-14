/**
 * Azalea Chatting Server
 *
 * Copyright (C) 2013-2015 Rex Lee <duguying2008@gmail.com>
 *
 * This program is free and opensource software; 
 * you can redistribute it and/or modify
 * it under the terms of the GNU General Public License
 */

#ifndef _COMMON_H_
#define _COMMON_H_

#if defined _WIN32
	#define az_exp __declspec(dllexport) 
#else
# 	define az_exp
#endif

#endif