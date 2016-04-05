//
//  MyLinkedLists.m
//  Data Structure Practice
//
//  Created by Travis Henspeter on 4/5/16.
//  Copyright © 2016 birdSound. All rights reserved.
//

#import "MyLinkedLists.h"

SinglyLinkedListNode*  CreateSinglyLinkedListNode(){
    
    SinglyLinkedListNode *node = (SinglyLinkedListNode *)malloc(sizeof(SinglyLinkedListNode));
    node->next = NULL;
    node->tag = -1;
    node->data = NULL;
    return node;
}

int SinglyLinkedListNodeCompare(SinglyLinkedListNode *node1, SinglyLinkedListNode *node2)
{
    if (node1->tag == node2->tag) {
        return 1;
    }
    
    return 0;
}


void SinglyLinkedListNodePrint(SinglyLinkedListNode *node){
    printf("\nnode with tag: %d has data: ",node->tag);
    float *data = (node->data);
    printf("%.1f",*data);
    printf("\t");
}

void DestroySinglyLinkedListNode(SinglyLinkedListNode *toDestroy){
    toDestroy->next = NULL;
    toDestroy->tag = -1;
    toDestroy->data = NULL;
    toDestroy->data_size = 0;
    free(toDestroy);
}

SinglyLinkedList* CreateSinglyLinkedList(){
    SinglyLinkedList *list = (SinglyLinkedList *)malloc(sizeof(SinglyLinkedList));
    list->length = 0;
    list->head = NULL;
    list->tail = NULL;
    return list;
}

SinglyLinkedListNode* SinglyLinkedListGetTail(SinglyLinkedList *list)
{
    SinglyLinkedListNode *node = list->head;
    while (node->next) {
        node = node->next;
    }
    
    return node;
}

void SinglyLinkedListInsertNode(SinglyLinkedList *list, SinglyLinkedListNode *toInsert, void* data){

    if (!list->head) {
        toInsert->data = (void*)data;
        list->head = toInsert;
        list->tail = list->head;
    }else{
        toInsert->data = (void*)data;
        list->tail->next = toInsert;
        list->tail = toInsert;
    }
    
    list->length++;
    //list->tail = SinglyLinkedListGetTail(list);
}

SinglyLinkedListNode*   SinglyLinkedListFindNode(SinglyLinkedList *list, SinglyLinkedListNode *toFind)
{
    SinglyLinkedListNode *node = list->head;
    
    while (node) {
        if (SinglyLinkedListNodeCompare(node, toFind)){
            break;
        }
        
        node = node->next;
    }
    
    return node;
}

void SinglyLinkedListDeleteNode(SinglyLinkedList *list, SinglyLinkedListNode *toDelete){
    
}

void SinglyLinkedListPrint(SinglyLinkedList *list)
{
    SinglyLinkedListNode *node = list->head;
    while (node) {
        SinglyLinkedListNodePrint(node);
        node = node->next;
    }
    
}

void DestroySinglyLinkedList(SinglyLinkedList *list)
{
    while (list->tail) {
        SinglyLinkedListDeleteNode(list, list->tail);
    }
    
    free(list);
}

@implementation MyLinkedLists



@end
