//
//  MyBinaryTreeTests.m
//  Data Structure Practice
//
//  Created by Travis Henspeter on 4/11/16.
//  Copyright © 2016 birdSound. All rights reserved.
//

#import <XCTest/XCTest.h>
#import "MyBinaryTrees.h"
#import "MySinglyLinkedLists.h"

@interface MyBinaryTreeTests : XCTestCase{
    BinaryTree *myBinaryTree;
    int dataCt;
    float dataMin;
    float dataMax;
    float *myDataArray;
}

@end

@implementation MyBinaryTreeTests

- (void)setUp {
    [super setUp];
    myBinaryTree = BinaryTreeCreate();
    myDataArray = (float *)malloc(sizeof(float) * dataCt);
    dataCt = 100;
    dataMin = 0.0;
    dataMax = 1000000;
    
    // Put setup code here. This method is called before the invocation of each test method in the class.
}

- (void)testInsert
{
    for (int i = 0; i < dataCt; i ++) {
        float rand = RandomFloatInRange(dataMin, dataMax);
        myDataArray[i] = rand;
        int result;
        BinaryTreeNode *root = myBinaryTree->root;
        result = BinaryTreeTraverseInOrder(myBinaryTree, root, (void *)&(myDataArray[i]), BinaryTreeInsert);
        //result = BinaryTreeInsert(myBinaryTree, root,(void *)&(myDataArray[i]));
        XCTAssert(result==0);
        XCTAssert(myBinaryTree->size == (i+1));
    }
    
    BinaryTreePrintInOrder(myBinaryTree);
    BinaryTreePrintPreOrder(myBinaryTree);
    BinaryTreePrintPostOrder(myBinaryTree);
}

- (void)testRemove
{
    [self testInsert];
    
    for (int i = (dataCt-1); i >= 0; i--) {
        float data = myDataArray[i];
        BinaryTreeNode *root = myBinaryTree->root;
        int result = BinaryTreeRemove(myBinaryTree,root,(void*)&data);
        XCTAssert(result==0);
        XCTAssert(myBinaryTree->size == (i-2));
    }
}

- (void)tearDown {
    // Put teardown code here. This method is called after the invocation of each test method in the class.
    [super tearDown];
    BinaryTreeDestroy(myBinaryTree);
    //free(myDataArray);
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
