//
//  MyStacks.m
//  Data Structure Practice
//
//  Created by Travis Henspeter on 4/6/16.
//  Copyright © 2016 birdSound. All rights reserved.
//

#import "MyStacks.h"

@implementation MyStacks

Stack* StackCreate(){
    Stack *stack = sll_init(NULL);
    return stack;
}

void StackDestroy(Stack *stack){
    sll_destroy(stack);
}

int StackPush(Stack *stack, void *data){
    return sll_insert_next(stack,stack->tail,data);
}

void* StackPop(Stack *stack){
    
    if (Stack_isEmpty(stack)) {
        return NULL;
    }
    sll_elem *element;
    
    if (stack->count == 1) {
        element = NULL;
    }else{
        element = stack->head;
        
        while (1) {
            
            if (element->next->next == NULL) {
                break;
            }
            
            element = element->next;
        }
    }
    
    void* data;
    sll_remove_next(stack,element,data);
    return data;
}

void* StackPeek(Stack *stack){
    
    if (Stack_isEmpty(stack)) {
        return NULL;
    }
    sll_elem *element;
    
    if (stack->count == 1) {
        element = NULL;
    }else{
        element = stack->head;
        
        while (1) {
            
            if (element->next->next == NULL) {
                break;
            }
            
            element = element->next;
        }
    }
    
    void* data = element->data;
    return data;
}

@end
