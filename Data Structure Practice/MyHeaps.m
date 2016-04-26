//
//  MyHeaps.m
//  Data Structure Practice
//
//  Created by Travis Henspeter on 4/6/16.
//  Copyright © 2016 birdSound. All rights reserved.
//

#import "MyHeaps.h"

@implementation MyHeaps

#define heap_parent(npos)   ((int)(((npos) - 1) / 2))
#define heap_left(npos)     (((npos) * 2) + 1)
#define heap_right(npos)    (((npos) * 2) + 2)


Heap* HeapCreate(int (*compare)(const void *key1, const void *key2), void (*destroy)(void *data))
{
    Heap *heap = (Heap *)(malloc(sizeof(Heap)));
    heap->compare = compare;
    heap->destroy = destroy;
    heap->size = 0;
    heap->tree = NULL;
    return heap;
}

void HeapDestroy(Heap *heap){
    if (heap->destroy != NULL){
        for (int i = 0; i < heap_size(heap); i++) {
            heap->destroy(heap->tree[i]);
        }
    }
    
    free(heap->tree);
    free(heap);
    memset(heap, 0, sizeof(Heap));
}

int HeapInsert(Heap *heap, const void *data){
    void *temp,*temp1;
    int ipos,ppos,mypos,myppos;
    if ((temp = (void **)realloc(heap->tree, (heap_size(heap) + 1) * sizeof(void *))) == NULL){
        return -1;
    }else{
        heap->tree = temp;
    }
    
    heap->tree[heap_size(heap)] = (void *)data;
    
    ipos = heap_size(heap);
    ppos = heap_parent(ipos);
    
    while (ipos > 0 && heap->compare(heap->tree[ppos],heap->tree[ipos]) < 0) {
        temp = heap->tree[ppos];
        heap->tree[ppos] = heap->tree[ipos];
        heap->tree[ipos] = temp;
        
        mypos = ipos;
        myppos = heap_parent(mypos);
        
        if (mypos > 0 && heap->compare(heap->tree[myppos],heap->tree[mypos])< 0){
            
            temp1 = heap->tree[myppos];
            heap->tree[myppos] = heap->tree[mypos];
            heap->tree[mypos] = temp1;
        }
        
        ipos = ppos;
        ppos = heap_parent(ipos);
    }
    
    heap->size++;
    
    return 0;
}
int HeapExtract(Heap *heap, void **data){
    void *save,*temp;
    int ipos,lpos,rpos,mpos;
    if (heap_size(heap) == 0){
        return -1;
    }
    *data = heap->tree[0];
    save = heap->tree[heap_size(heap) - 1];
    
    if ((heap_size(heap) - 1) > 0){
        if ((temp = (void **)realloc(heap->tree, (heap_size(heap) - 1) * sizeof(void*))) == NULL){
            return -1;
        }else{
            heap->tree = temp;
        }
        
        heap->size--;
    }else{
        
        free(heap->tree);
        heap->tree = NULL;
        heap->size = 0;
        return 0;
    }
    
    heap->tree[0] = save;
    ipos = 0;
    lpos = heap_left(ipos);
    rpos = heap_right(ipos);
    
    while (1) {
        if (lpos < heap_size(heap) && heap->compare(heap->tree[lpos],heap->tree[ipos]) > 0){
            mpos = lpos;
        }else{
            mpos = ipos;
        }
        if (rpos < heap_size(heap) && heap->compare(heap->tree[rpos],heap->tree[ipos]) > 0){
            mpos = rpos;
        }
        
        if (mpos == ipos) {
            break;
        }else{
            temp = heap->tree[mpos];
            heap->tree[mpos] = heap->tree[ipos];
            heap->tree[ipos] = temp;
            
            ipos = mpos;
        }
    }
    
    return 0;
}
@end
