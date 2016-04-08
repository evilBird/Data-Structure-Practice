//
//  MyChainedHashTables.h
//  Data Structure Practice
//
//  Created by Travis Henspeter on 4/6/16.
//  Copyright © 2016 birdSound. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "MySinglyLinkedLists.h"

#define cht             ChainedHashTable
#define cht_init        ChainedHashTableCreate
#define cht_insert      ChainedHashTableInsert
#define cht_lookup      ChainedHashTableLookup
#define cht_remove      ChainedHashTableRemove
#define cht_destroy     ChainedHashTableDestroy

#define hash_string     MyStringHashFunction
#define hash_int        MyIntegerHashFunction
#define hash_float      MyFloatHashFunction
//#define hash_mult       MyMultiplicationMethodHashFunction

#define cht_bucket(bucket)      &(hashTable->table[bucket])
#define cht_bucket_head(bucket) (cht_bucket(bucket))->head

@interface MyChainedHashTables : NSObject

typedef struct MyChainedHashTable{
    int buckets;
    int (*h)(const void *key);
    int (*match)(const void *key1, const void *key2);
    void(*destroy)(void *data);
    int size;
    SinglyLinkedList    *table;
}ChainedHashTable;


int MyStringHashFunction(const void *key);
int MyIntegerHashFunction(const void *key);
int MyFloatHashFunction(const void *key);

//int MyMultiplicationMethodHashFunction(const void *key, int n);

ChainedHashTable* ChainedHashTableCreate(int buckets,
                                         int (*h)(const void *key),
                                         int (*match)(const void *key1, const void *key2),
                                         void (*destroy)(void *data));

void ChainedHashTableDestroy(ChainedHashTable *hashTable);
int ChainedHashTableInsert(ChainedHashTable *hashTable, const void *data);
int ChainedHashTableRemove(ChainedHashTable *hashTable, void **data);
int ChainedHashTableLookup(ChainedHashTable *hashTable, void **data);


@end
