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
#define _DS_H_

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>

typedef enum etype etype;
///element type
enum etype{inte , floate , stringe , doublee , structe};
//        0     , 1      , 2       , 3       , 4

///basic data struct node
typedef struct _Node Node;
struct _Node
{
	etype   type;
	int     int_value;
	float   float_value;
	char*   string_value;
	double  double_value;
	void*   struct_value;
	Node*   next;
	Node*   prev;
};

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

/**
 * create a struct varible node
 * @param  struct_content the pointer of the struct
 * @return                [description]
 */
Node* create_node_struct(void* struct_content);

#endif
