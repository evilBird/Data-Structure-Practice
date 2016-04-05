//
//  MyLinkedLists.h
//  Data Structure Practice
//
//  Created by Travis Henspeter on 4/5/16.
//  Copyright © 2016 birdSound. All rights reserved.
//

#import <Foundation/Foundation.h>

typedef struct MySinglyLinkedListNode{
    void                                *data;
    size_t                              data_size;
    int                                 tag;
    struct MySinglyLinkedListNode       *next;
    
}SinglyLinkedListNode;

SinglyLinkedListNode*   CreateSinglyLinkedListNode();
int                     SinglyLinkedListNodeCompare(SinglyLinkedListNode *node1, SinglyLinkedListNode *node2);
void                    SinglyLinkedListNodePrint(SinglyLinkedListNode *node);
void                    DestroySinglyLinkedListNode(SinglyLinkedListNode *toDestroy);

typedef struct MySinglyLinkedList{
    SinglyLinkedListNode              *head;
    SinglyLinkedListNode              *tail;
    int                               length;
}SinglyLinkedList;

SinglyLinkedList*   CreateSinglyLinkedList();
void                DestroySinglyLinkedList(SinglyLinkedList *list);

void SinglyLinkedListInsertNode(SinglyLinkedList *list, SinglyLinkedListNode *toInsert, void* data);
void SinglyLinkedListDeleteNode(SinglyLinkedList *list, SinglyLinkedListNode *toDelete);
SinglyLinkedListNode*   SinglyLinkedListFindNode(SinglyLinkedList *list, SinglyLinkedListNode *toFind);
void SinglyLinkedListPrint(SinglyLinkedList *list);

@interface MyLinkedLists : NSObject

@end
