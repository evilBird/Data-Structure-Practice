//
//  MyLinkedLists.h
//  Data Structure Practice
//
//  Created by Travis Henspeter on 4/5/16.
//  Copyright © 2016 birdSound. All rights reserved.
//

#import <Foundation/Foundation.h>

#define sll_init            SinglyLinkedListCreate
#define sll_append          SinglyLinkedListAppend
#define sll_insert_next     SinglyLinkedListInsertNext
#define sll_remove_next     SinglyLinkedListRemoveNext
#define sll_destroy         SinglyLinkedListDestroy

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

int SinglyLinkedListAppend(SinglyLinkedList *list,
                            void* data);

int SinglyLinkedListRemoveNext(SinglyLinkedList *list,
                                SinglyLinkedListElement *element,
                                void **data);

void SinglyLinkedListPrint(SinglyLinkedList *list);

void SinglyLinkedListDestroy(SinglyLinkedList *list);

@end
