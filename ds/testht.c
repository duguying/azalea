#include <stdio.h>
#include "hashtable.h"

int main(void){
	struct HashTable hash_table;
	ht_init(&hash_table);
	ht_insert(&hash_table,"rex", 123);
	hash_table_print(&hash_table);
	return 0;
}