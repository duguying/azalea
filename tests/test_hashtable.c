/**
 * Azalea Chatting Server
 *
 * Copyright (C) 2013-2015 Rex Lee <duguying2008@gmail.com>
 *
 * This program is free and opensource software; 
 * you can redistribute it and/or modify
 * it under the terms of the GNU General Public License
 */

#include "apis/hashtable.h"

int main(void){
	HashTable* hash_table;
	// HashNode* lookup_result;

	hash_table=ht_init(10000);
	
	ht_insert(hash_table,"i", create_node_int(12));
	ht_insert(hash_table,"s", create_node_string("this is a string!"));	

	// ht_print(hash_table);

	// ht_remove(hash_table,"i");
	// printf("%s",ht_lookup(hash_table,"s")->string_value);
	
	ht_print(hash_table);
	ht_destroy(hash_table);
	return 0;
}