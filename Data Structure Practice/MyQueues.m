//
//  MyQueues.m
//  Data Structure Practice
//
//  Created by Travis Henspeter on 4/6/16.
//  Copyright © 2016 birdSound. All rights reserved.
//

#import "MyQueues.h"

@implementation MyQueues

Queue* QueueCreate(){
    
    Queue *queue = sll_init(NULL);
    return queue;
}

void QueueDestroy(Queue *queue){
    sll_destroy(queue);
}

int QueueEnqueue(Queue *queue, void* data){
    int result = sll_insert_next(queue,queue->tail,data);
    return result;
}

void* QueueDeenqeue(Queue *queue){
    
    if (Queue_isEmpty(queue)) {
        return NULL;
    }
    
    void* data;
    sll_remove_next(queue,NULL,&data);
    return data;
}

void* QueuePeek(Queue *queue){
    if (Queue_isEmpty(queue)) {
        return NULL;
    }
    
    void* data = queue->head->data;
    return data;
}

@end
