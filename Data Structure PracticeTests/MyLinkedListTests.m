//
//  MyLinkedListTests.m
//  Data Structure Practice
//
//  Created by Travis Henspeter on 4/5/16.
//  Copyright © 2016 birdSound. All rights reserved.
//

#import <XCTest/XCTest.h>
#import "MyLinkedLists.h"

@interface MyLinkedListTests : XCTestCase {
    SinglyLinkedList *mySinglyLinkedList;
}

@end

@implementation MyLinkedListTests

- (void)setUp {
    [super setUp];
    mySinglyLinkedList = NULL;
    mySinglyLinkedList = CreateSinglyLinkedList();
    XCTAssert(NULL!=mySinglyLinkedList);
    // Put setup code here. This method is called before the invocation of each test method in the class.
}

- (void)tearDown {
    // Put teardown code here. This method is called after the invocation of each test method in the class.
    [super tearDown];
    //DestroySinglyLinkedList(mySinglyLinkedList);
    mySinglyLinkedList = NULL;
    XCTAssert(NULL==mySinglyLinkedList);
}

float random_list_data()
{
    int range = 10;
    unsigned int  random_int = arc4random_uniform(range);
    float random_float = ((float)random_int) - (float)range/2.;
    return random_float;
}

- (void)testSinglyLinkedListDataInsert
{
    int length = 10;
    float list_data[10] = {};
    for (int i = 0; i<length; i++) {
        float random_data = random_list_data();
        list_data[i] = random_data;
        SinglyLinkedListNode *toInsert = CreateSinglyLinkedListNode();
        toInsert->tag = i;
        SinglyLinkedListInsertNode(mySinglyLinkedList, toInsert,(void *)(&random_data));
        printf("\ninserted data value %.1f at index %d",random_data,i);
        SinglyLinkedListNodePrint(toInsert);
        SinglyLinkedListPrint(mySinglyLinkedList);
    }
    
    XCTAssertTrue(mySinglyLinkedList->length==length);
    SinglyLinkedListNode *node = mySinglyLinkedList->head;
    
    for (int i = 0; i < length; i++) {
        float *node_data = (float *)node->data;
        float node_data_val = *node_data;
        float list_data_val = list_data[i];
        XCTAssertTrue(node_data_val==list_data_val,"node data value %.1f does not match list data value %.1f at index %d",node_data_val,list_data_val,i);
        node = node->next;
    }
}



- (void)testExample {
    // This is an example of a functional test case.
    // Use XCTAssert and related functions to verify your tests produce the correct results.
}

- (void)testPerformanceExample {
    // This is an example of a performance test case.
    [self measureBlock:^{
        // Put the code you want to measure the time of here.
    }];
}

@end
