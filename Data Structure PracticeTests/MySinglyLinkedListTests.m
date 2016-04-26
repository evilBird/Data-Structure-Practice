//
//  MyLinkedListTests.m
//  Data Structure Practice
//
//  Created by Travis Henspeter on 4/5/16.
//  Copyright © 2016 birdSound. All rights reserved.
//

#import <XCTest/XCTest.h>
#import "MySinglyLinkedLists.h"
#import "MyDataStructureUtils.h"

#define DEFAULT_LENGTH 10

@interface MySinglyLinkedListTests : XCTestCase {
    SinglyLinkedList *mySinglyLinkedList;
    int              length;
    float            list_data[DEFAULT_LENGTH];
}

@end

@implementation MySinglyLinkedListTests

- (void)testSinglyLinkedListAppend
{
    SinglyLinkedListElement *element = mySinglyLinkedList->head;
    for (int i = 0; i < length; i++) {
        XCTAssertTrue((*(float*)(element->data)) == list_data[i],@"data in singly linked list element at index %d = %f does not match inserted data %f",i,(*(float*)(element->data)),list_data[i]);
        element = element->next;
    }
    
    SinglyLinkedListPrintVisual(mySinglyLinkedList, FormatFloatData);
}

- (void)testSinglyLinkedListPrintVisual
{
    SinglyLinkedList *list = SinglyLinkedListCreate(MatchIntegersFunction);
    int n = DEFAULT_LENGTH;
    
    for (int i = 0; i < n; i ++) {
        int *integerData = (int*)(malloc(sizeof(int)));
        *integerData = arc4random_uniform(1000);
        SinglyLinkedListAppend(list, (void*)integerData);
    }
    
    SinglyLinkedListPrintVisual(list, FormatIntegerData);
}

- (void)testSinglyLinkedListPrint
{
    SinglyLinkedList *list = SinglyLinkedListCreate(MatchIntegersFunction);
    int n = DEFAULT_LENGTH;
    void* theData[DEFAULT_LENGTH];
    
    for (int i = 0; i < n; i ++) {
        int *integerData = (int*)(malloc(sizeof(int)));
        *integerData = arc4random_uniform(1000);
        theData[i] = (void*)integerData;
        SinglyLinkedListAppend(list, (void*)integerData);
    }
    
    SinglyLinkedListPrintVisual(list, FormatIntegerData);
    SinglyLinkedListElement *e = NULL;
    void *toFind;
    int randomIndex = arc4random_uniform(DEFAULT_LENGTH);
    toFind = theData[randomIndex];
    printf("\nfind data = %d\n",(*(int*)toFind));
    e = SinglyLinkedListSearch(list, toFind);
    XCTAssert(e!=NULL);
    printf("\nfound data = %d\n",(*(int*)(e->data)));
    
    int *toInsert = (int*)(malloc(sizeof(int)));
    *toInsert = (*(int*)(e->data));
    SinglyLinkedListInsertNext(list, e, toInsert);
    SinglyLinkedListPrintVisual(list, FormatIntegerData);
    
}

- (void)testSinglyLinkedListSearch
{
    int indexToSearch = arc4random_uniform(length);
    SinglyLinkedListElement *result = NULL;
    result = SinglyLinkedListSearch(mySinglyLinkedList, (void *)(&(list_data[indexToSearch])));
    XCTAssert(NULL!=result);
}

- (void)testSinglyLinkedListSearchAndInsertAfterElement
{
    int randomIdx = (int)arc4random_uniform(length-1);
    float newData = rand_float();
    SinglyLinkedListInsertNext(mySinglyLinkedList, SinglyLinkedListSearch(mySinglyLinkedList, (void *)(&(list_data[randomIdx]))), (void *)(&newData));
    SinglyLinkedListElement *thePrecedingElement = SinglyLinkedListSearch(mySinglyLinkedList, (void *)(&(list_data[randomIdx])));
    XCTAssert(NULL!=thePrecedingElement);
    SinglyLinkedListElement *theInsertedElement = thePrecedingElement->next;
    XCTAssert(NULL!=theInsertedElement);
    XCTAssert(*((float *)(theInsertedElement->data))==newData);
}

- (void)testSinglyLinkedListRemoveElements
{
    do {
        void *myData;
        int prevCount = mySinglyLinkedList->count;
        int result = SinglyLinkedListRemoveNext(mySinglyLinkedList, NULL, &myData);
        XCTAssert(result==0);
        XCTAssert(mySinglyLinkedList->count>prevCount);
    } while (mySinglyLinkedList->count);
}

- (void)setUp {
    [super setUp];
    length = DEFAULT_LENGTH;
    mySinglyLinkedList = NULL;
    mySinglyLinkedList = SinglyLinkedListCreate(NULL);
    XCTAssert(NULL!=mySinglyLinkedList);

    for (int i = 0; i<length; i++) {
        list_data[i] = rand_float();
        SinglyLinkedListAppend(mySinglyLinkedList, (void *)(&(list_data[i])));
    }
    
    XCTAssert(mySinglyLinkedList->count==length);
}

- (void)tearDown {
    [super tearDown];
    SinglyLinkedListDestroy(mySinglyLinkedList);
    XCTAssert(mySinglyLinkedList->count==0);
    mySinglyLinkedList = NULL;
    XCTAssert(NULL==mySinglyLinkedList);
}


@end
