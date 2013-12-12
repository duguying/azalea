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
	for (i = 0; i < 1000; ++i)
	{
		ht_init(&hash_table);
		ht_insert(&hash_table,"rex", 123);
		ht_insert(&hash_table,"lee", 123);
		ht_insert(&hash_table,"lijun", 12346);
		hash_table_print(&hash_table);
		ht_remove(&hash_table,"rex");
		hash_table_print(&hash_table);
		lookup_result=ht_lookup(&hash_table,"lijun");
		printf("the key:%s  the value:%d\n", lookup_result->sKey, lookup_result->nValue);
		printf("\n%s\n", "After release");
		ht_release(&hash_table);
		hash_table_print(&hash_table);
	}
	return 0;
}