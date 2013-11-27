/**
 * @file hashtable.c
 * @brief hashtable
 * @author Rex Lee duguying2008@gmail.com
 * @version 0.01
 * @date 2013-10-20
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashtable.h"

/**
 * @brief initial the hashtable
 * @details this function not alloc memory for HashTable pointer
 * 
 * @param HashTable the pointer of hashtable
 */
void ht_init(struct HashTable* hash_table)
{
    memset(hash_table, 0, sizeof(struct HashTable));
    hash_table->ht_size= 0;  //the number of key-value pairs in the hash table!
}

/**
 * string hash function
 * @param  skey [description]
 * @return      [description]
 */
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


/**
 * @brief insert key-value into hash table
 * @details [long description]
 * 
 * @param HashTable the hashtable
 * @param skey key
 * @param nvalue value
 */
void ht_insert(struct HashTable* hash_table, const char* skey, int nvalue)
{
    if(hash_table->ht_size >= HASH_TABLE_MAX_SIZE)
    {
        printf("out of hash table memory!\n");
        return;
    }
    unsigned int pos = ht_hash_str(skey) % HASH_TABLE_MAX_SIZE;
    struct HashNode* pHead =  hash_table->table[pos];
    while(pHead)
    {
        if(strcmp(pHead->sKey, skey) == 0)
        {
            printf("%s already exists!\n", skey);
            return ;
        }
        pHead = pHead->pNext;
    }
    struct HashNode* pNewNode = (struct HashNode*)malloc(sizeof(struct HashNode));
    memset(pNewNode, 0, sizeof(struct HashNode));
    pNewNode->sKey = (char*)malloc(sizeof(char) * (strlen(skey) + 1));
    strcpy(pNewNode->sKey, skey);
    pNewNode->nValue = nvalue;
    pNewNode->pNext = hash_table->table[pos];
    hash_table->table[pos] = pNewNode;

    hash_table->ht_size++;
}


void hash_table_print(struct HashTable* hash_table)
{
    printf("===========content of hash table=================\n");
    int i;
    for (i = 0; i < HASH_TABLE_MAX_SIZE; ++i)
        if (hash_table->table[i])
        {
            struct HashNode *pHead = hash_table->table[i];
            printf("%d=>", i);
            while (pHead)
            {
                printf("%s:%d  ", pHead->sKey, pHead->nValue);
                pHead = pHead->pNext;
            }
            printf("\n");
        }
}


/**
 * @brief remove the hash node from hashtable
 * @details [long description]
 * 
 * @param HashTable the hashtable
 * @param skey the key of hashtable you'll remove
 */
void ht_remove(struct HashTable* hash_table, const char* skey)
{
    unsigned int pos = ht_hash_str(skey) % HASH_TABLE_MAX_SIZE;
    if(hash_table->table[pos])
    {
        struct HashNode* pHead = hash_table->table[pos];
        struct HashNode* pLast = NULL;
        struct HashNode* pRemove = NULL;
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
                hash_table->table[pos] = NULL;
            free(pRemove->sKey);
            free(pRemove);
        }
    }
}

/**
 * lookup a key in the hash table
 * @param  skey key
 * @return      value
 */
// HashNode* ht_lookup(HashNode* hashTable, const char* skey)
// {
//     unsigned int pos = ht_hash_str(skey) % HASH_TABLE_MAX_SIZE;
//     if(hashTable[pos])
//     {
//         HashNode* pHead = hashTable[pos];
//         while(pHead)
//         {
//             if(strcmp(skey, pHead->sKey) == 0)
//                 return pHead;
//             pHead = pHead->pNext;
//         }
//     }
//     return NULL;
// }

/**
 * free the memory of the hash table
 */
// void ht_release(HashNode* hashTable)
// {
//     int i;
//     for(i = 0; i < HASH_TABLE_MAX_SIZE; ++i)
//     {
//         if(hashTable[i])
//         {
//             HashNode* pHead = hashTable[i];
//             while(pHead)
//             {
//                 HashNode* pTemp = pHead;
//                 pHead = pHead->pNext;
//                 if(pTemp)
//                 {
//                     free(pTemp->sKey);
//                     free(pTemp);
//                 }
//             }
//         }
//     }
// }

