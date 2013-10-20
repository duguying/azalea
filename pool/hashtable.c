/// @file hashtable.c
/// @brief hashtable
/// @author Rex Lee duguying2008@gmail.com
/// @version 0.01
/// @date 2013-10-20
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashtable.h"

HashNode* hashTable[HASH_TABLE_MAX_SIZE]; //hash table data strcutrue
int ht_size;  //the number of key-value pairs in the hash table!

/// @brief ht_init initialize hash table
void ht_init()
{
    ht_size = 0;
    memset(hashTable, 0, sizeof(HashNode*) * HASH_TABLE_MAX_SIZE);
}

/// @brief ht_hash_str string hash function
///
/// @param skey
///
/// @return 
unsigned int ht_hash_str(const char* skey)
{
    const signed char *p = (const signed char*)skey;
    unsigned int h = *p;
    if(h)
    {
        for(p += 1; *p != '\0'; ++p)
            h = (h << 5) - h + *p;
    }
    return h;
}

/// @brief ht_insert insert key-value into hash table
///
/// @param skey
/// @param nvalue
void ht_insert(const char* skey, int nvalue)
{
    if(ht_size >= HASH_TABLE_MAX_SIZE)
    {
        printf("out of hash table memory!\n");
        return;
    }
    unsigned int pos = ht_hash_str(skey) % HASH_TABLE_MAX_SIZE;
    HashNode* pHead =  hashTable[pos];
    while(pHead)
    {
        if(strcmp(pHead->sKey, skey) == 0)
        {
            printf("%s already exists!\n", skey);
            return ;
        }
        pHead = pHead->pNext;
    }
    HashNode* pNewNode = (HashNode*)malloc(sizeof(HashNode));
    memset(pNewNode, 0, sizeof(HashNode));
    pNewNode->sKey = (char*)malloc(sizeof(char) * (strlen(skey) + 1));
    strcpy(pNewNode->sKey, skey);
    pNewNode->nValue = nvalue;
    pNewNode->pNext = hashTable[pos];
    hashTable[pos] = pNewNode;

    ht_size++;
}

/// @brief ht_remove remove key-value frome the hash table
///
/// @param skey
void ht_remove(const char* skey)
{
    unsigned int pos = ht_hash_str(skey) % HASH_TABLE_MAX_SIZE;
    if(hashTable[pos])
    {
        HashNode* pHead = hashTable[pos];
        HashNode* pLast = NULL;
        HashNode* pRemove = NULL;
        while(pHead)
        {
            if(strcmp(skey, pHead->sKey) == 0)
            {
                pRemove = pHead;
                break;
            }
            pLast = pHead;
            pHead = pHead->pNext;
        }
        if(pRemove)
        {
            if(pLast)
                pLast->pNext = pRemove->pNext;
            else
                hashTable[pos] = NULL;
            free(pRemove->sKey);
            free(pRemove);
        }
    }
}

/// @brief ht_lookup lookup a key in the hash table
///
/// @param skey
///
/// @return 
HashNode* ht_lookup(const char* skey)
{
    unsigned int pos = ht_hash_str(skey) % HASH_TABLE_MAX_SIZE;
    if(hashTable[pos])
    {
        HashNode* pHead = hashTable[pos];
        while(pHead)
        {
            if(strcmp(skey, pHead->sKey) == 0)
                return pHead;
            pHead = pHead->pNext;
        }
    }
    return NULL;
}

//print the content in the hash table
/*
void ht_print()
{
    printf("===========content of hash table=================\n");
    int i;
    for(i = 0; i < HASH_TABLE_MAX_SIZE; ++i)
        if(hashTable[i])
        {
            HashNode* pHead = hashTable[i];
            printf("%d=>", i);
            while(pHead)
            {
                printf("%s:%d  ", pHead->sKey, pHead->nValue);
                pHead = pHead->pNext;
            }
            printf("\n");
        }
}
*/

/// @brief ht_release free the memory of the hash table
void ht_release()
{
    int i;
    for(i = 0; i < HASH_TABLE_MAX_SIZE; ++i)
    {
        if(hashTable[i])
        {
            HashNode* pHead = hashTable[i];
            while(pHead)
            {
                HashNode* pTemp = pHead;
                pHead = pHead->pNext;
                if(pTemp)
                {
                    free(pTemp->sKey);
                    free(pTemp);
                }
            }
        }
    }
}

