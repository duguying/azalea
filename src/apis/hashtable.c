/**
 * Azalea Chatting Server
 *
 * Copyright (C) 2013-2015 Rex Lee <duguying2008@gmail.com>
 *
 * This program is free and opensource software; 
 * you can redistribute it and/or modify
 * it under the terms of the GNU General Public License
 */

#include "hashtable.h"

HashTable* ht_init(int size){
    HashTable* ht_pointer;
    ht_pointer=(HashTable*)malloc(sizeof(HashTable));
    memset(ht_pointer, 0, sizeof(HashTable));
    ht_pointer->ht_max_size=size;
    ht_pointer->table=(HashNode**)malloc(sizeof(HashNode*)*ht_pointer->ht_max_size);
    memset(ht_pointer->table,0,sizeof(HashNode*)*ht_pointer->ht_max_size);
    ht_pointer->ht_size= 0;
    return ht_pointer;
}

unsigned int ht_hash_function(const char* skey)
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

int ht_insert(HashTable* hash_table, const char* skey, Node* pvalue){
	unsigned int pos;
	HashNode* pHead;
	HashNode* pNewNode;

    ///if hashtable size is over, return
    if(hash_table->ht_size >= hash_table->ht_max_size)
    {
        printf("out of hash table memory!\n");
        return IERROR;
    }
    ///caculate the position of hashnode list
    pos = ht_hash_function(skey) % hash_table->ht_max_size;
    ///set the head of node list
    pHead = *(hash_table->table+pos);
    while(pHead)
    {
        ///check whether the key is exist
        if(strcmp(pHead->sKey, skey) == 0)
        {
            // printf("%s already exists!\n", skey);
            if (pvalue!=NULL)  // free the node
            {
                free(pvalue);
            }
            return IERROR;
        }
        pHead = pHead->pNext;
    }
    pNewNode = (HashNode*)malloc(sizeof(HashNode));
    memset(pNewNode, 0, sizeof(HashNode));
    pNewNode->sKey = (char*)malloc(sizeof(char) * (strlen(skey) + 1));
    strcpy(pNewNode->sKey, skey);
    pNewNode->pValue = pvalue;
    pNewNode->pNext = hash_table->table[pos];
    hash_table->table[pos] = pNewNode;
    hash_table->ht_size++;
    return 0;
}

void ht_remove(HashTable* hash_table, const char* skey){
    unsigned int pos = ht_hash_function(skey) % hash_table->ht_max_size;

    if(hash_table->table[pos])
    {
        HashNode* pHead = hash_table->table[pos];
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
            else{
                free(hash_table->table[pos]->pValue);
                hash_table->table[pos] = NULL;
            }
                
            free(pRemove->sKey);
            free(pRemove);
        }
    }
}

Node* ht_lookup(HashTable* hash_table, const char* skey){
    HashNode* pHead;
    unsigned int pos = ht_hash_function(skey) % hash_table->ht_max_size;
    
    if(hash_table->table[pos])
    {
        pHead = hash_table->table[pos];
        while(pHead)
        {
            if(strcmp(skey, pHead->sKey) == 0){
                return hash_table->table[pos]->pValue;
            }else{
                pHead = pHead->pNext;
            }
            
        }
    }
    return NULL;
}

void ht_destroy(HashTable* hash_table){
    int i;
    HashNode* pTemp;
    HashNode* pHead;

    for(i = 0; i < hash_table->ht_max_size; ++i)
    {
        if(hash_table->table[i])
        {
            pHead = hash_table->table[i];
            while(pHead)
            {
                pTemp = pHead;
                pHead = pHead->pNext;
                if(pTemp)
                {
                    free(pTemp->sKey);
                    free(pTemp->pValue);
                    free(pTemp);
                }
            }
        }
    }
    free(hash_table->table);
    free(hash_table);
    hash_table=NULL;
}

//========================================================

void ht_print(HashTable* hash_table){
    int i;

    printf("===========content of hash table=================\n");
    for (i = 0; i < hash_table->ht_max_size; ++i)
        if (hash_table->table[i])
        {
            HashNode *pHead = hash_table->table[i];
            printf("%d=>", i);
            while (pHead)
            {
                printf("%s:[%p]",pHead->sKey, pHead->pValue);
                if(inte==pHead->pValue->type){
                    printf("(%d)",pHead->pValue->int_value);
                }else if(floate==pHead->pValue->type){
                    printf("(%f)",pHead->pValue->float_value);
                }else if(doublee==pHead->pValue->type){
                    printf("(%lf)",pHead->pValue->double_value);
                }else if(stringe==pHead->pValue->type){
                    printf("(%s)",pHead->pValue->string_value);
                }else if(structe==pHead->pValue->type){
                    printf("(%p)",pHead->pValue->struct_value);
                }
                pHead = pHead->pNext;
            }
            printf("\n");
        }
}
