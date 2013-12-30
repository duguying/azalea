/**
 * Azalea Chatting Server
 *
 * Copyright (C) 2013-2015 Rex Lee <duguying2008@gmail.com>
 *
 * This program is free and opensource software; 
 * you can redistribute it and/or modify
 * it under the terms of the GNU General Public License
 */

#ifndef _DS_H_
///this file is just include by other files in ds dir
#define _DS_H_

#include "ichat.h"

/**
 * @brief create a int stack node
 * @details [long description]
 * 
 * @param value [description]
 * @return [description]
 */
Node* create_node_int(int value);

/**
 * @brief create a string stack node
 * @details [long description]
 * 
 * @param value [description]
 * @return [description]
 */
Node* create_node_float(float value);

/**
 * @brief create a double stack node
 * @details [long description]
 * 
 * @param value [description]
 * @return [description]
 */
Node* create_node_double(double value);

/**
 * @brief create a string stack node
 * @details [long description]
 * 
 * @param value [description]
 * @return [description]
 */
Node* create_node_string(const char* value);

#endif