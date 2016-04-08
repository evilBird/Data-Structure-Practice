//
//  MyQueues.h
//  Data Structure Practice
//
//  Created by Travis Henspeter on 4/6/16.
//  Copyright © 2016 birdSound. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "MySinglyLinkedLists.h"

@interface MyQueues : NSObject

#define Queue     SinglyLinkedList
#define Queue_isEmpty(queue)   ((queue)->count == 0 ? 1 : 0)

Queue* QueueCreate();
void QueueDestroy(Queue *queue);
int QueueEnqueue(Queue *queue, void* data);
void* QueueDeenqeue(Queue *queue);
void* QueuePeek(Queue *queue);



@end
