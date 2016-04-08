//
//  MyStackTests.m
//  Data Structure Practice
//
//  Created by Travis Henspeter on 4/8/16.
//  Copyright © 2016 birdSound. All rights reserved.
//

#import <XCTest/XCTest.h>
#import "MyStacks.h"

@interface MyStackTests : XCTestCase{
    Stack *myStack;
}

@end

@implementation MyStackTests

- (void)setUp {
    [super setUp];
    myStack = StackCreate();
    
    // Put setup code here. This method is called before the invocation of each test method in the class.
}

- (void)testStack{
    
    float inputData[100] = {};
    int i;
    for (i = 0; i < 100; i ++) {
        inputData[i] = (float)arc4random_uniform(100000);
        void* inputDatum = (void*)&(inputData[i]);
        StackPush(myStack, inputDatum);
    }
    
    float inputValue;
    void* outputDatum;
    float outputValue = 0;
    for (i = 99; i > 0; --i) {
        inputValue = inputData[i];
        outputDatum = StackPop(myStack);
        outputValue = *(float*)outputDatum;
        XCTAssert(inputValue==outputValue);
    }
}

- (void)tearDown {
    // Put teardown code here. This method is called after the invocation of each test method in the class.
    [super tearDown];
    StackDestroy(myStack);
}


@end
