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
    int                                  count;
    
}SinglyLinkedList;

SinglyLinkedList* SinglyLinkedListCreate();

int SinglyLinkedListCountElements(SinglyLinkedList *list);

SinglyLinkedListElement* SinglyLinkedListSearch(SinglyLinkedList *list,
                                                    void *toFind);

int SinglyLinkedListInsertNext(SinglyLinkedList *list,
                                            SinglyLinkedListElement *element,
                                            void *toInsert);

int SinglyLinkedListInsertNextData(SinglyLinkedList *list,
                                    void *toFind,
                                    void *toInsert);

int SinglyLinkedListAppend(SinglyLinkedList *list,
                            void* data);

int SinglyLinkedListRemoveNext(SinglyLinkedList *list,
                                SinglyLinkedListElement *element,
                                void **data);

int SinglyLinkedListRemoveNextData(SinglyLinkedList *list,
                                    void *toFind,
                                    void **data);

void SinglyLinkedListPrint(SinglyLinkedList *list);

void SinglyLinkedListDestroy(SinglyLinkedList *list);

@end
