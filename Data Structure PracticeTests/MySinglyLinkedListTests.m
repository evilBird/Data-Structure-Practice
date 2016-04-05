//
//  MyLinkedListTests.m
//  Data Structure Practice
//
//  Created by Travis Henspeter on 4/5/16.
//  Copyright © 2016 birdSound. All rights reserved.
//

#import <XCTest/XCTest.h>
#import "MySinglyLinkedLists.h"

@interface MySinglyLinkedListTests : XCTestCase {
    SinglyLinkedList *mySinglyLinkedList;
}

@end

@implementation MySinglyLinkedListTests

- (void)setUp {
    [super setUp];
    mySinglyLinkedList = NULL;
    mySinglyLinkedList = SinglyLinkedListCreate();
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
        SinglyLinkedListElement *toInsert = SinglyLinkedListElementCreate();
        toInsert->tag = i;
        SinglyLinkedListInsertElement(mySinglyLinkedList, toInsert,(void *)(&random_data));
        printf("\ninserted data value %.1f at index %d",random_data,i);
        SinglyLinkedListElementPrint(toInsert);
        SinglyLinkedListPrint(mySinglyLinkedList);
    }
    
    XCTAssertTrue(mySinglyLinkedList->length==length);
    SinglyLinkedListElement *element = mySinglyLinkedList->head;
    
    for (int i = 0; i < length; i++) {
        float *element_data = (float *)element->data;
        float elem_data_val = *element_data;
        float list_data_val = list_data[i];
        XCTAssertTrue(elem_data_val==list_data_val,"element data value %.1f does not match list data value %.1f at index %d",elem_data_val,list_data_val,i);
        element = element->next;
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
