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
    struct MySinglyLinkedListElement    *next;
    
}SinglyLinkedListElement;

SinglyLinkedListElement* SinglyLinkedListElementCreate();

void SinglyLinkedListElementPrint(SinglyLinkedListElement *element);

void SinglyLinkedListElementDestroy(SinglyLinkedListElement *toDestroy);


typedef struct MySinglyLinkedList{
    
    SinglyLinkedListElement              *head;
    SinglyLinkedListElement              *tail;
    
}SinglyLinkedList;

SinglyLinkedList* SinglyLinkedListCreate();

int SinglyLinkedListCountElements(SinglyLinkedList *list);

SinglyLinkedListElement* SinglyLinkedListSearch(SinglyLinkedList *list,
                                                    void *toFind);

void SinglyLinkedListInsertNext(SinglyLinkedList *list,
                                            SinglyLinkedListElement *element,
                                            void *toInsert);

void SinglyLinkedListInsertNextData(SinglyLinkedList *list,
                                    void *toFind,
                                    void *toInsert);

void SinglyLinkedListAppend(SinglyLinkedList *list,
                            void* data);

void SinglyLinkedListRemoveNext(SinglyLinkedList *list,
                                SinglyLinkedListElement *element,
                                void **data);

void SinglyLinkedListRemoveNextData(SinglyLinkedList *list,
                                    void *toFind,
                                    void **data);

void SinglyLinkedListPrint(SinglyLinkedList *list);

void SinglyLinkedListDestroy(SinglyLinkedList *list);

@end
