/**
 * Azalea Chatting Server
 *
 * Copyright (C) 2013-2015 Rex Lee <duguying2008@gmail.com>
 *
 * This program is free and opensource software; 
 * you can redistribute it and/or modify
 * it under the terms of the GNU General Public License
 */

#include <stdio.h>
#include "../src/ds/hashtable.h"

int main(void){
	HashTable hash_table;
	HashNode* lookup_result;
	int i;
	ht_init(&hash_table);
	for (i = 0; i < 1000; ++i)
	{
		ht_insert(&hash_table,"i", i);	
	}
	hash_table_print(&hash_table);
	ht_release(&hash_table);
	hash_table_print(&hash_table);
	return 0;
}