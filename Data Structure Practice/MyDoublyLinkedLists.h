//
//  MyDoublyLinkedLists.h
//  Data Structure Practice
//
//  Created by Travis Henspeter on 4/6/16.
//  Copyright © 2016 birdSound. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface MyDoublyLinkedLists : NSObject

typedef struct MyDoublyLinkedListElement {
    void                                *data;
    struct MyDoublyLinkedListElement    *next;
    struct MyDoublyLinkedListElement    *prev;
} DoublyLinkedListElement;

DoublyLinkedListElement*    DoublyLinkedListElementCreate();
int  DoublyLinkedLinkElementCompareFloat(void *element1, void *element2);
void DoublyLinkedListElementPrint(DoublyLinkedListElement *element);

typedef struct MyDoublyLinkedList{
    DoublyLinkedListElement     *head;
    DoublyLinkedListElement     *tail;
    int                         count;
    int                         (*match)(const void *key1, const void *key2);
}DoublyLinkedList;

DoublyLinkedList* DoublyLinkedListCreate();

int DoublyLinkedListAppend(DoublyLinkedList *list, void *data);
int DoublyLinkedListSearch(DoublyLinkedList *list, int (*compare)(const void *key1, const void *key2),void *data);
int DoublyLinkedListInsertNext(DoublyLinkedList *list, DoublyLinkedListElement *element, void *data);
int DoublyLinkedListInsertPrevious(DoublyLinkedList *list, DoublyLinkedListElement *element, void *data);
int DoublyLinkedListRemoveNext(DoublyLinkedList *list, DoublyLinkedListElement *element, void **data);
int DoublyLinkedListRemovePrevious(DoublyLinkedList *list, DoublyLinkedListElement *element, void **data);
void DoublyLinkedListDestroy(DoublyLinkedList *list);

@end
