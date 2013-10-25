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

/// @brief ht_insert insert key-value into hash table
///
/// @param skey
/// @param nvalue
void ht_insert(const char* skey, int nvalue);

/// @brief ht_remove remove key-value frome the hash table
///
/// @param skey
void ht_remove(const char* skey);

/// @brief ht_lookup lookup a key in the hash table
///
/// @param skey
///
/// @return 
HashNode* ht_lookup(const char* skey);
