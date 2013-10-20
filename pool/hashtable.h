/// @file hashtable.h
/// @brief hash table
/// @author Rex Lee duguying2008@gmail.com
/// @version 0.01
/// @date 2013-10-20
#include <stdio.h>
#include <stdlib.h>

#define HASH_TABLE_MAX_SIZE 10000
typedef struct HashNode_Struct HashNode;
struct HashNode_Struct
{
    char* sKey;
    int nValue;
    HashNode* pNext;
};

/// @brief ht_init hash table initialize 
void ht_init();

/// @brief ht_insert hash table insert
void ht_insert();

/// @brief ht_remove hash table remove
void ht_remove();
