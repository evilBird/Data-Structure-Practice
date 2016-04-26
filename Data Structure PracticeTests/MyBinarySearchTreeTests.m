//
//  MyBinarySearchTreeTests.m
//  Data Structure Practice
//
//  Created by Travis Henspeter on 4/12/16.
//  Copyright © 2016 birdSound. All rights reserved.
//

#import <XCTest/XCTest.h>
#import "MyBinarySearchTrees.h"
#import "MySinglyLinkedLists.h"

#define TestUtil_GetDataPtr(i)  ((void*)(&(myData[i])))

@interface MyBinarySearchTreeTests : XCTestCase{
    BinarySearchTree    *myBinarySearchTree;
    int                 kDataCount;
    float               *myData;
    float               kMinData;
    float               kMaxData;
}

@end

@implementation MyBinarySearchTreeTests

- (void)setUp {
    [super setUp];
    kDataCount = 100;
    kMinData = 0;
    kMaxData = 1000000;
    myData = (float *)malloc(sizeof(float) * kDataCount + 1);
    myBinarySearchTree = BinarySearchTreeCreate(BinarySearchTreeNode_CompareFloats);
    // Put setup code here. This method is called before the invocation of each test method in the class.
}


- (void)testInsertData{
    myData[0] = RandomFloatInRange(kMinData, kMaxData);
    BinarySearchTreeNode *node = NULL;
    int b;
    int result = BinarySearchTreeInsert(myBinarySearchTree, &node, (void *)(&(myData[0])), &b);
    node = myBinarySearchTree->root;
    XCTAssert(node!=NULL);
    
    for (int i = 1; i < kDataCount; i ++) {
        myData[i] = RandomFloatInRange(kMinData, kMaxData);
        int factor;
        result = BinarySearchTreeInsert(myBinarySearchTree, &node, TestUtil_GetDataPtr(i), &factor);
        XCTAssert(result==0);
    }
    
    BinarySearchTreePrintInOrder(myBinarySearchTree, NULL, NULL);
}

- (void)tearDown {
    // Put teardown code here. This method is called after the invocation of each test method in the class.
    [super tearDown];
    //BinarySearchTreeDestroy(myBinarySearchTree);
    //free(myData);
}

- (void)testExample {

    BinarySearchTree *tree = BinarySearchTreeCreate(BinarySearchTreeNode_CompareInts);
    int kTreeDataCount = 12;
    void* treeData[12];
    for (int i = 0; i < kTreeDataCount; i++) {
        int* randomInt = (int*)malloc(sizeof(int));
        *randomInt = arc4random_uniform(30);
        treeData[i] = (void*)randomInt;
        int balanced;
        BinarySearchTreeNode *node = tree->root;
        BinarySearchTreeInsert(tree, &node, (void *)randomInt, &balanced);
        
    }
    
    BinarySearchTreePrintVisual(tree, FormatIntegerData);
}

- (void)testPerformanceExample {
    // This is an example of a performance test case.
    [self measureBlock:^{
        // Put the code you want to measure the time of here.
    }];
}

@end
