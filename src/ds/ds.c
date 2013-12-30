/**
 * Azalea Chatting Server
 *
 * Copyright (C) 2013-2015 Rex Lee <duguying2008@gmail.com>
 *
 * This program is free and opensource software; 
 * you can redistribute it and/or modify
 * it under the terms of the GNU General Public License
 */

#include "ds.h"

 /**
 * @brief create a int stack node
 * @details [long description]
 * 
 * @param value [description]
 * @return [description]
 */
Node* create_node_int(int value){
	Node* sn=(Node*)malloc(sizeof(Node));
	sn->type=inte;
	sn->int_value=value;
	return sn;
}

/**
 * @brief create a string stack node
 * @details [long description]
 * 
 * @param value [description]
 * @return [description]
 */
Node* create_node_float(float value){
	Node* sn=(Node*)malloc(sizeof(Node));
	sn->type=floate;
	sn->float_value=value;
	return sn;
}

/**
 * @brief create a double stack node
 * @details [long description]
 * 
 * @param value [description]
 * @return [description]
 */
Node* create_node_double(double value){
	Node* sn=(Node*)malloc(sizeof(Node));
	sn->type=doublee;
	sn->double_value=value;
	return sn;
}

/**
 * @brief create a string stack node
 * @details [long description]
 * 
 * @param value [description]
 * @return [description]
 */
Node* create_node_string(const char* value){
	Node* sn=(Node*)malloc(sizeof(Node));
	sn->type=stringe;
	sn->string_value=(char*)value;
	return sn;
}
