/// @file hashtable.h
/// @brief hash table
/// @author Rex Lee duguying2008@gmail.com
/// @version 0.01
/// @date 2013-10-20
#include <stdio.h>
#include <stdlib.h>

#define HASH_TABLE_MAX_SIZE 10000

struct HashNode
{
    char* sKey;
    int nValue;
    struct HashNode* pNext;
};


struct HashTable
{
	int ht_size;
	struct HashNode* table[HASH_TABLE_MAX_SIZE];
};


