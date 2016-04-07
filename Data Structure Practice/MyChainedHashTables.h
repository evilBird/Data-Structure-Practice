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
#define cht_hash_str    MyStringHashFunction
#define cht_hash_int    MyIntegerHashFunction
#define cht_hash_gen    MyGeneralHashFunction
#define key2int         CoerceKeyToInteger
#define match_any       MyGeneralMatchFunction

@interface MyChainedHashTables : NSObject

typedef struct MyChainedHashTable{
    int buckets;
    int (*h)(const void *key, const int n);
    int (*match)(const void *key1, const void *key2);
    void(*destroy)(void *data);
    int size;
    SinglyLinkedList    *table;
}ChainedHashTable;


int MyStringHashFunction(const void *key, const int n);
int MyGeneralHashFunction(const void *key, const int n);
int MyIntegerHashFunction(const void *key, const int n);
int CoerceKeyToInteger(const void *key, const int n);
int MyGeneralMatchFunction(const void *key1, const void *key2);

ChainedHashTable* ChainedHashTableCreate(int buckets,
                                         int (*h)(const void *key, const int n),
                                         int (*match)(const void *key1, const void *key2),
                                         void (*destroy)(void *data));

void ChainedHashTableDestroy(ChainedHashTable *hashTable);

int ChainedHashTableInsert(ChainedHashTable *hashTable, const void *data);
int ChainedHashTableRemove(ChainedHashTable *hashTable, void **data);
int ChainedHashTableLookup(ChainedHashTable *hashTable, void **data);

@end
