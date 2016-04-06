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

- (void)testSinglyLinkedListAppend
{
    int length = 10;
    float list_data[10] = {};
    for (int i = 0; i<length; i++) {
        list_data[i] = random_list_data(100);
        SinglyLinkedListAppend(mySinglyLinkedList, (void *)(&(list_data[i])));
    }
    SinglyLinkedListElement *element = mySinglyLinkedList->head;
    
    for (int i = 0; i < length; i++) {
        XCTAssertTrue((*(float*)(element->data)) == list_data[i],@"data in singly linked list element at index %d = %f does not match inserted data %f",i,(*(float*)(element->data)),list_data[i]);
        element = element->next;
    }
}

- (void)testSinglyLinkedListPrint
{
    int length = 10;
    float list_data[10] = {};
    for (int i = 0; i<length; i++) {
        list_data[i] = random_list_data(100);
        SinglyLinkedListAppend(mySinglyLinkedList, (void *)(&(list_data[i])));
        SinglyLinkedListElementPrint(mySinglyLinkedList->tail);
    }
}

- (void)testSinglyLinkedListCount
{
    int length = 10;
    float list_data[10] = {};
    for (int i = 0; i<length; i++) {
        list_data[i] = random_list_data(100);
        SinglyLinkedListAppend(mySinglyLinkedList, (void *)(&(list_data[i])));
    }
    
    XCTAssert(mySinglyLinkedList->count == length);
    
}

- (void)testSinglyLinkedListSearch
{
    int length = 10;
    float list_data[10] = {};
    for (int i = 0; i<length; i++) {
        list_data[i] = random_list_data(100);
        SinglyLinkedListAppend(mySinglyLinkedList, (void *)(&(list_data[i])));
    }
    
    int indexToSearch = arc4random_uniform(length);
    SinglyLinkedListElement *result = NULL;
    result = SinglyLinkedListSearch(mySinglyLinkedList, (void *)(&(list_data[indexToSearch])));
    XCTAssert(NULL!=result);
}

- (void)testSinglyLinkedListSearchAndInsertAfterElement
{
    int length = 10;
    float list_data[10] = {};
    for (int i = 0; i<length; i++) {
        list_data[i] = random_list_data(100);
        SinglyLinkedListAppend(mySinglyLinkedList, (void *)(&(list_data[i])));
    }
    
    int randomIdx = (int)arc4random_uniform(length-1);
    float newData = random_list_data(100);
    SinglyLinkedListInsertNext(mySinglyLinkedList, SinglyLinkedListSearch(mySinglyLinkedList, (void *)(&(list_data[randomIdx]))), (void *)(&newData));
    SinglyLinkedListElement *thePrecedingElement = SinglyLinkedListSearch(mySinglyLinkedList, (void *)(&(list_data[randomIdx])));
    XCTAssert(NULL!=thePrecedingElement);
    SinglyLinkedListElement *theInsertedElement = thePrecedingElement->next;
    XCTAssert(NULL!=theInsertedElement);
    XCTAssert(*((float *)(theInsertedElement->data))==newData);
}

- (void)testSinglyLinkedListRemoveElements
{
    int length = 10;
    float list_data[10] = {};
    
    for (int i = 0; i<length; i++) {
        list_data[i] = random_list_data(100);
        SinglyLinkedListAppend(mySinglyLinkedList, (void *)(&(list_data[i])));
    }
    
    int i = length;
    while (mySinglyLinkedList->count) {

        void *myData;
        int prevCount = mySinglyLinkedList->count;
        int result = SinglyLinkedListRemoveNext(mySinglyLinkedList, NULL, &myData);
        
        if (result != 0) {
            break;
        }
        
        XCTAssert(mySinglyLinkedList->count = (prevCount-1),@"expected count = %d, actual count = %d",prevCount,mySinglyLinkedList->count);
        
        if (&(*myData)) {
            float myDataValue = *(float*)(&(*myData));
            float listDataValue = list_data[i];
            XCTAssert(myDataValue==listDataValue,@"expected data value = %.2f, actual data value = %.2f",listDataValue,myDataValue);
        }
    }
}

- (void)setUp {
    [super setUp];
    mySinglyLinkedList = NULL;
    mySinglyLinkedList = SinglyLinkedListCreate();
    XCTAssert(NULL!=mySinglyLinkedList);
}

- (void)tearDown {
    [super tearDown];
    SinglyLinkedListDestroy(mySinglyLinkedList);
    XCTAssert(mySinglyLinkedList->count==0);
    mySinglyLinkedList = NULL;
    XCTAssert(NULL==mySinglyLinkedList);
}

float random_list_data(int range)
{
    unsigned int  random_int = arc4random_uniform(range);
    float random_float = ((float)random_int) - (float)range/2.;
    return random_float;
}

@end
