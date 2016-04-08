//
//  MyQueueTests.m
//  Data Structure Practice
//
//  Created by Travis Henspeter on 4/8/16.
//  Copyright © 2016 birdSound. All rights reserved.
//

#import <XCTest/XCTest.h>
#import "MyQueues.h"

@interface MyQueueTests : XCTestCase{
    Queue *myQueue;
}

@end

@implementation MyQueueTests

- (void)setUp {
    [super setUp];
    myQueue = QueueCreate();
    
    // Put setup code here. This method is called before the invocation of each test method in the class.
}

- (void)testQueue
{
    int inputData[100] = {};
    for (int i = 0; i < 100; i ++) {
        inputData[i] = arc4random_uniform(100000);
        void* inputDatum = (void*)&(inputData[i]);
        QueueEnqueue(myQueue, inputDatum);
    }
    
    int inputValue;
    void* outputDatum;
    int outputValue;
    
    for (int i = 0; i < 100; i++) {
        inputValue = inputData[i];
        outputDatum = QueueDeenqeue(myQueue);
        outputValue = *(int*)outputDatum;
        XCTAssert(inputValue==outputValue);
    }
}

- (void)tearDown {
    // Put teardown code here. This method is called after the invocation of each test method in the class.
    [super tearDown];
    QueueDestroy(myQueue);
}

@end
