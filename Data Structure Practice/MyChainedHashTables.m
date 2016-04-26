//
//  MyChainedHashTables.m
//  Data Structure Practice
//
//  Created by Travis Henspeter on 4/6/16.
//  Copyright © 2016 birdSound. All rights reserved.
//

#import "MyChainedHashTables.h"
@implementation MyChainedHashTables

int MyStringHashFunction(const void *key)
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
    
    return val;
}

int MyIntegerHashFunction(const void *key){
    
    int k = *(int *)key;
    char keyString[100];
    sprintf(keyString, "%d",k);
    int val = MyStringHashFunction((void*)keyString);
    return val;
}

int MyFloatHashFunction(const void *key){
    
    float k = *(float *)key;
    char keyString[100];
    sprintf(keyString, "%f",k);
    int val = MyStringHashFunction((void*)keyString);
    return val;
}

int MyMultiplicationMethodHashFunction(const void *key, int n){
    
    int k = *(int *)key;
    float A = 0.618;
    float fract;
    float remainder = modff((k*A), &fract);
    int val = (int)(n * remainder) % n;
    return val;
}

ChainedHashTable* ChainedHashTableCreate(int buckets,
                                         int (*h)(const void *key),
                                         int (*match)(const void *key1, const void *key2),
                                         void (*destroy)(void *data)){
    
    ChainedHashTable *hashTable = NULL;
    hashTable = (ChainedHashTable *)malloc(sizeof(ChainedHashTable) + 1);
    
    if (!hashTable) {
        return NULL;
    }
    
    hashTable->table = malloc(sizeof(SinglyLinkedList)*buckets + 1);
    hashTable->buckets = buckets;
    
    for (int i = 0; i < hashTable->buckets; i ++) {
        hashTable->table[i] = *sll_init(NULL);
    }
    
    hashTable->h = h;
    hashTable->match = match;
    hashTable->destroy = destroy;
    hashTable->size = 0;
    
    return hashTable;
}

void ChainedHashTableDestroy(ChainedHashTable *hashTable){
    free(hashTable->table);
    memset(hashTable->table, 0, sizeof(SinglyLinkedList));
    free(hashTable);
    memset(hashTable, 0, sizeof(ChainedHashTable));
}

int ChainedHashTableLookup(ChainedHashTable *hashTable, void **data){
    int bucket;
    bucket = hashTable->h(*data) % hashTable->buckets;
    SinglyLinkedListElement *element;
    for (element = cht_bucket_head(bucket); element != NULL; element = element->next) {
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
    
    if (cht_lookup(hashTable, &temp) == 0) {
        return 1;
    }
    
    bucket = hashTable->h(data) % hashTable->buckets;
    
    if ((retval = sll_insert_next(cht_bucket(bucket),NULL, (void *)temp)) == 0) {
        hashTable->size++;
    }
    return retval;
}

int ChainedHashTableRemove(ChainedHashTable *hashTable, void **data){
    
    SinglyLinkedListElement *element,*prev;
    int bucket;
    bucket = hashTable->h(*data) % hashTable->buckets;
    prev = NULL;
    
    for (element = cht_bucket_head(bucket); element != NULL; element = element->next) {
        if (hashTable->match(*data, element->data)) {
            if (sll_remove_next(cht_bucket(bucket),prev, data) == 0 ) {
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
