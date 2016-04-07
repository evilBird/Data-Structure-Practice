//
//  MyChainedHashTables.m
//  Data Structure Practice
//
//  Created by Travis Henspeter on 4/6/16.
//  Copyright © 2016 birdSound. All rights reserved.
//

#import "MyChainedHashTables.h"

@implementation MyChainedHashTables

int MyStringHashFunction(const void *key, const int n)
{
    const char *ptr;
    unsigned int val;
    val = 0;
    ptr = key;
    
    while (*ptr != '\0') {
        unsigned int tmp;
        val = ( val << 4 ) + ( *ptr );
        if ( (tmp = ( val & 0xf0000000 )) ) {
            val = val ^ (tmp >> 24);
            val = val ^ tmp;
        }
        
        ptr++;
    }
    
    return ( val % n );
}

int MyIntegerHashFunction(const void *key,const int n){
    
    int k = *(int *)key;
    float A = 0.618;
    float fract;
    float remainder = modff((k*A), &fract);
    int val = (int)(n * remainder) % n;
    
    return val;
}

int CoerceKeyToInteger(const void *key, const int n){
    int *ptr = (int *)key;
    int ct = 0;
    float val = 0;
    float B = 1699.;
    
    do {
        int ptrVal = *ptr;
        val += logf(n + ((float)ptrVal/(float)(ct + 1)))/logf(B/(float)ptrVal+0.00001);
        ptr++;
        ct ++;
    } while (*ptr);
    
    int keyAsInteger = roundf(val);
    keyAsInteger*=keyAsInteger;
    
    return keyAsInteger;
}

int MyGeneralHashFunction(const void *key, const int n){
    int keyAsInteger = CoerceKeyToInteger(key, n);
    return MyIntegerHashFunction((void *)&keyAsInteger, n);
}

int MyGeneralMatchFunction(const void *key1, const void *key2){
    int n = 1699;
    int hash1 = MyGeneralHashFunction(key1, n);
    int hash2 = MyGeneralHashFunction(key2, n);
    return (hash1 - hash2);
}

ChainedHashTable* ChainedHashTableCreate(int buckets,
                                         int (*h)(const void *key, const int n),
                                         int (*match)(const void *key1, const void *key2),
                                         void (*destroy)(void *data)){
    
    ChainedHashTable *hashTable = NULL;
    hashTable = (ChainedHashTable *)malloc(sizeof(ChainedHashTable));
    if (!hashTable) {
        return NULL;
    }
    
    hashTable->table = malloc(sizeof(SinglyLinkedList)*buckets);
    hashTable->buckets = buckets;
    SinglyLinkedList *ptr = hashTable->table;
    for (int i = 0; i < hashTable->buckets; i ++) {
        SinglyLinkedList *sll = sll_init(NULL);
        *ptr = *sll;
        ptr += sizeof(SinglyLinkedList);
    }
    
    hashTable->h = h;
    hashTable->match = match;
    hashTable->destroy = destroy;
    hashTable->size = 0;
    
    return hashTable;
}

void ChainedHashTableDestroy(ChainedHashTable *hashTable){
    for (int i = 0; i < hashTable->buckets; i ++) {
        SinglyLinkedListDestroy(&(hashTable->table[i]));
    }
    free(hashTable->table);
    free(hashTable);
    memset(hashTable, 0, sizeof(ChainedHashTable));
}

int ChainedHashTableLookup(ChainedHashTable *hashTable, void **data){
    SinglyLinkedListElement *element;
    int bucket;
    bucket = hashTable->h(*data, hashTable->buckets);
    SinglyLinkedList myList = (hashTable->table[bucket]);
    
    //for (element = *((&hashTable->table[bucket].head)); element != NULL; element = element->next) {
    for (element = myList.head; element != NULL; element = element->next) {
        if (hashTable->match(*data, element->data)) {
            *data = (void *)element->data;
            return 0;
        }
    }
    return -1;
}

int ChainedHashTableInsert(ChainedHashTable *hashTable, const void *data){
    void *temp;
    int bucket;
    int retval;
    temp = (void *)data;
    
    if (ChainedHashTableLookup(hashTable, &temp) == 0) {
        return 1;
    }
    
    bucket = hashTable->h(data, hashTable->buckets);
    if ((retval = sll_insert_next(&hashTable->table[bucket],NULL, (void *)data)) == 0) {
        hashTable->size++;
    }
    return retval;
}

int ChainedHashTableRemove(ChainedHashTable *hashTable, void **data){
    
    SinglyLinkedListElement *element,*prev;
    int bucket;
    bucket = hashTable->h(*data, hashTable->buckets);
    prev = NULL;
    for (element = *((&hashTable->table[bucket].head)); element != NULL; element = element->next) {
        if (hashTable->match(*data, element->data)) {
            if (sll_remove_next(&hashTable->table[bucket],prev, data) == 0 ) {
                hashTable->size--;
                return 0;
            }else{
                return -1;
            }
        }
        
        prev = element;
    }
    
    return 0;
}

@end
