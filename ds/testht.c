#include <stdio.h>
#include "hashtable.h"

int main(void){
	HashTable hash_table;
	HashNode* lookup_result;
	int i;
	for (i = 0; i < 100000; ++i)
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