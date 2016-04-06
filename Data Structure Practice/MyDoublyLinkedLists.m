//
//  MyDoublyLinkedLists.m
//  Data Structure Practice
//
//  Created by Travis Henspeter on 4/6/16.
//  Copyright © 2016 birdSound. All rights reserved.
//

#import "MyDoublyLinkedLists.h"

@implementation MyDoublyLinkedLists

DoublyLinkedListElement*    DoublyLinkedListElementCreate()
{
    return NULL;
}
int  DoublyLinkedLinkElementCompareFloat(void *element1, void *element2) { return 0; }
void DoublyLinkedListElementPrint(DoublyLinkedListElement *element) {}
int DoublyLinkedListAppend(DoublyLinkedList *list, void *data) {return 0;}
int DoublyLinkedListSearch(DoublyLinkedList *list, int (*compare)(const void *key1, const void *key2),void *data){ return 0; }
int DoublyLinkedListInsertNext(DoublyLinkedList *list, DoublyLinkedListElement *element, void *data){ return 0; }
int DoublyLinkedListInsertPrevious(DoublyLinkedList *list, DoublyLinkedListElement *element, void *data){ return 0; }
int DoublyLinkedListRemoveNext(DoublyLinkedList *list, DoublyLinkedListElement *element, void **data){ return 0; }
int DoublyLinkedListRemovePrevious(DoublyLinkedList *list, DoublyLinkedListElement *element, void **data){ return 0; }
void DoublyLinkedListDestroy(DoublyLinkedList *list){  }

@end
