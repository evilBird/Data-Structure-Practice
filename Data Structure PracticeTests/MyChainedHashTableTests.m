//
//  MyChainedHashTableTests.m
//  Data Structure Practice
//
//  Created by Travis Henspeter on 4/6/16.
//  Copyright © 2016 birdSound. All rights reserved.
//

#import <XCTest/XCTest.h>
#import "MyChainedHashTables.h"

#define DEFAULT_BUCKETS 2000
#define DEFAULT_DATA_COUNT 4000

@interface MyChainedHashTableTests : XCTestCase {
    ChainedHashTable *myChainedHashTable;
    int              numBuckets;
    float            *myData;
    int              myDataCount;
}

@end

@implementation MyChainedHashTableTests

- (void)setUp {
    [super setUp];
    numBuckets = DEFAULT_BUCKETS;
    myDataCount = DEFAULT_DATA_COUNT;
    // Put setup code here. This method is called before the invocation of each test method in the class.
}

- (void)testInsert
{
    myData = (float *)malloc(sizeof(float) * myDataCount + 1);
    myChainedHashTable = cht_init(numBuckets, hash_float, match_float, NULL);
    
    for (int i = 0; i < myDataCount; i ++) {
        myData[i] = rand_float_b(0,16789);
        void* toInsert = (void *)&(myData[i]);
        int result = cht_insert(myChainedHashTable,toInsert);
        XCTAssert(result > -1);
    }
}

- (void)testLookup
{
    [self testInsert];
    for (int i = 0; i < myDataCount; i ++) {
        void* toLookup = (void*)&(myData[i]);
        int result = cht_lookup(myChainedHashTable, &toLookup);
        XCTAssert(result>-1, @"value %f not found",myData[i]);
    }
}

- (void)testRemove
{
    [self testInsert];
    for (int i = 0; i < myDataCount; i ++) {
        void* toLookup = (void*)&(myData[i]);
        int result = cht_remove(myChainedHashTable, &toLookup);
        result = cht_lookup(myChainedHashTable, &toLookup);
        XCTAssert(result==-1);
    }
}

- (void)tearDown {
    // Put teardown code here. This method is called after the invocation of each test method in the class.
    [super tearDown];
    cht_destroy(myChainedHashTable);
    myChainedHashTable = NULL;
    free(myData);
    myData = NULL;
}


@end
