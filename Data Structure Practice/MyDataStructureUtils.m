//
//  MyDataStructureUtils.m
//  Data Structure Practice
//
//  Created by Travis Henspeter on 4/14/16.
//  Copyright © 2016 birdSound. All rights reserved.
//

#import "MyDataStructureUtils.h"

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

int CompareIntegerKeys(const void *key1, const void *key2){
    return ((*((int*)key1)) - (*((int*)key2)));
}


@implementation MyDataStructureUtils


@end
