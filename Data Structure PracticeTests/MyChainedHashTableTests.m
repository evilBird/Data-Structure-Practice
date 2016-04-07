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
    int             myDataCount;
}

@end

@implementation MyChainedHashTableTests

- (void)setUp {
    [super setUp];
    numBuckets = DEFAULT_BUCKETS;
    myDataCount = DEFAULT_DATA_COUNT;
    myChainedHashTable = cht_init(numBuckets, cht_hash_gen, match_float, NULL);
    [self generateMyData];
    
    // Put setup code here. This method is called before the invocation of each test method in the class.
}

- (void)generateMyData
{
    myData = (float *)malloc(sizeof(float) * myDataCount);
    for (int i = 0; i < myDataCount; i ++) {
        float value = rand_float_b(0,16789);
        myData[i] = value;
        printf("\n%.2f",myData[i]);
    }
}

- (void)testInsertAndLookupData
{
    for (int i = 0; i < myDataCount; i ++) {
        float value = myData[i];
        void* myInput = (void *)(&value);
        int result = cht_insert(myChainedHashTable, myInput);
        printf("\nkey %.f insert result = %d",value,result);
        XCTAssert(result!=-1);
        printf("\nhash table size: %d",myChainedHashTable->size);
        result = cht_lookup(myChainedHashTable, &myInput);
        printf("\nkey %.f lookup result = %d",value,result);
    }
}

- (void)tearDown {
    // Put teardown code here. This method is called after the invocation of each test method in the class.
    [super tearDown];
}

- (void)testMyGeneralHashFunctionWithIntegers
{
    int output;
    int prevOutput;
    
    void* input;
    int integerInput = arc4random_uniform(1000);
    input = (void *)&integerInput;
    output = cht_hash_gen(input, numBuckets);
    XCTAssert(output>0&&output<numBuckets);
    printf("\ngeneral integer input %d hashes to %d\n\n\n",integerInput,output);
    
    prevOutput = output;
    integerInput = arc4random_uniform(1000);
    input = (void *)&integerInput;
    output = cht_hash_gen(input, numBuckets);
    XCTAssert(output>0&&output<numBuckets);
    XCTAssert(output!=prevOutput);
    printf("\ngeneral integer input %d hashes to %d\n\n\n",integerInput,output);
    
    prevOutput = output;
    integerInput = arc4random_uniform(1000);
    input = (void *)&integerInput;
    output = cht_hash_gen(input, numBuckets);
    XCTAssert(output>0&&output<numBuckets);
    printf("\ngeneral integer input %d hashes to %d\n\n\n",integerInput,output);
    
    prevOutput = output;
    integerInput = arc4random_uniform(1000);
    input = (void *)&integerInput;
    output = cht_hash_gen(input, numBuckets);
    XCTAssert(output>0&&output<numBuckets);
    XCTAssert(output!=prevOutput);
    printf("\ngeneral integer input %d hashes to %d\n\n\n",integerInput,output);
}


- (void)testMyGeneralHashFunctionWithStrings
{
    int output;
    int prevOutput;
    
    void* input;
    char* stringInput = "this is a string";
    input = (void *)stringInput;
    output = cht_hash_gen(input, numBuckets);
    XCTAssert(output>0&&output<numBuckets);
    XCTAssert(output!=prevOutput);
    printf("\ngeneral string input %s hashes to %d\n\n\n",stringInput,output);
    
    prevOutput = output;
    stringInput = "this is another string";
    input = (void *)stringInput;
    output = cht_hash_gen(input, numBuckets);
    XCTAssert(output>0&&output<numBuckets);
    XCTAssert(output!=prevOutput);
    printf("\ngeneral string input %s hashes to %d\n\n\n",stringInput,output);
    
    prevOutput = output;
    stringInput = "this is still another string";
    input = (void *)stringInput;
    output = cht_hash_gen(input, numBuckets);
    XCTAssert(output>0&&output<numBuckets);
    XCTAssert(output!=prevOutput);
    printf("\ngeneral string input %s hashes to %d\n\n\n",stringInput,output);
    
    prevOutput = output;
    stringInput = "this is the final string...for now";
    input = (void *)stringInput;
    output = cht_hash_gen(input, numBuckets);
    XCTAssert(output>0&&output<numBuckets);
    XCTAssert(output!=prevOutput);
    printf("\ngeneral string input %s hashes to %d\n\n\n",stringInput,output);
}

@end
