//
//  MyStacks.h
//  Data Structure Practice
//
//  Created by Travis Henspeter on 4/6/16.
//  Copyright © 2016 birdSound. All rights reserved.
//

#import "MySinglyLinkedLists.h"

@interface MyStacks : NSObject

#define Stack   SinglyLinkedList
#define Stack_isEmpty(stack)    ((stack)->count == 0 ? 1 : 0)

Stack* StackCreate();
void StackDestroy(Stack *stack);
int StackPush(Stack *stack, void *data);
void* StackPop(Stack *stack);
void* StackPeek(Stack *stack);

@end
