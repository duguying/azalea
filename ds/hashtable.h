/// @file hashtable.h
/// @brief hash table
/// @author Rex Lee duguying2008@gmail.com
/// @version 0.01
/// @date 2013-10-20
#include <stdio.h>
#include <stdlib.h>

#define HASH_TABLE_MAX_SIZE 10000

typedef struct HashNode HashNode;

struct HashNode
{
    char* sKey;
    int nValue;
    HashNode* pNext;
} ;

typedef struct HashTable HashTable;

struct HashTable
{
	int ht_size;
	HashNode* table[HASH_TABLE_MAX_SIZE];
};

HashNode* ht_lookup(HashTable* hash_table, const char* skey);
