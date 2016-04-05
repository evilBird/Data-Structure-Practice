//
//  MyLinkedLists.h
//  Data Structure Practice
//
//  Created by Travis Henspeter on 4/5/16.
//  Copyright © 2016 birdSound. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface MySinglyLinkedLists : NSObject

typedef struct MySinglyLinkedListElement{
    
    void                                *data;
    int                                 tag;
    struct MySinglyLinkedListElement    *next;
    
}SinglyLinkedListElement;

SinglyLinkedListElement* SinglyLinkedListElementCreate();

int SinglyLinkedListElementCompare(SinglyLinkedListElement *element1, SinglyLinkedListElement *element2);

void SinglyLinkedListElementPrint(SinglyLinkedListElement *element);

void SinglyLinkedListNodeDestroy(SinglyLinkedListElement *toDestroy);


typedef struct MySinglyLinkedList{
    
    SinglyLinkedListElement              *head;
    SinglyLinkedListElement              *tail;
    int                                 length;
    
}SinglyLinkedList;

SinglyLinkedList* SinglyLinkedListCreate();

void SinglyLinkedListDestroy(SinglyLinkedList *list);

void SinglyLinkedListInsertElement(SinglyLinkedList *list, SinglyLinkedListElement *toInsert, void* data);

void SinglyLinkedListDeleteElement(SinglyLinkedList *list, SinglyLinkedListElement *toDelete);

SinglyLinkedListElement* SinglyLinkedListFindElement(SinglyLinkedList *list, SinglyLinkedListElement *toFind);

void SinglyLinkedListPrint(SinglyLinkedList *list);

@end
