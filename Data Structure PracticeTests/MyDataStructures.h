//
//  MyDataStructures.h
//  Data Structure Practice
//
//  Created by Travis Henspeter on 4/14/16.
//  Copyright © 2016 birdSound. All rights reserved.
//

#ifndef MyDataStructures_h
#define MyDataStructures_h

#import <Foundation/Foundation.h>

#import "MySinglyLinkedLists.h"
#import "MyStacks.h"
#import "MyQueues.h"
#import "MyChainedHashTables.h"
#import "MyBinaryTrees.h"
#import "MyBinarySearchTrees.h"
#import "MyHeaps.h"

void* RandomIntegerData(){
    
    void* myData = (void *)(malloc(sizeof(int)));
    int myRandomInteger = arc4random_uniform(10000);
    memset(myData,myRandomInteger,sizeof(int));
    
    return myData;
}

void** RandomIntegerDataArray(int n){
    
    void** myDataArray = (void **)(malloc(sizeof(void *) * (n + 1)));
    for (int i = 0; i < n; i++) {
        myDataArray[i] = RandomIntegerData();
    }
    
    return myDataArray;
}

#endif /* MyDataStructures_h */
