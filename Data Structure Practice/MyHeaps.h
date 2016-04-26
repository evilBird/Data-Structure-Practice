//
//  MyHeaps.h
//  Data Structure Practice
//
//  Created by Travis Henspeter on 4/6/16.
//  Copyright © 2016 birdSound. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface MyHeaps : NSObject

typedef struct Heap_{
    int     size;
    
    int     (*compare)(const void *key1, const void *key2);
    void    (*destroy)(void *data);
    
    void    **tree;
}Heap;

Heap* HeapCreate(int (*compare)(const void *key1, const void *key2), void (*destroy)(void *data));
void HeapDestroy(Heap *heap);
int HeapInsert(Heap *heap, const void *data);
int HeapExtract(Heap *heap, void **data);

#define heap_size(heap) ((heap)->size)


@end
