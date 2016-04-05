//
//  MyLinkedLists.m
//  Data Structure Practice
//
//  Created by Travis Henspeter on 4/5/16.
//  Copyright © 2016 birdSound. All rights reserved.
//

#import "MySinglyLinkedLists.h"

@implementation MySinglyLinkedLists

SinglyLinkedListElement*  SinglyLinkedListElementCreate(){
    
    SinglyLinkedListElement *element = (SinglyLinkedListElement *)malloc(sizeof(SinglyLinkedListElement));
    element->next = NULL;
    element->tag = -1;
    element->data = NULL;
    return element;
}

int SinglyLinkedListElementCompare(SinglyLinkedListElement *element1, SinglyLinkedListElement *element2)
{
    if (element1->tag == element2->tag) {
        return 1;
    }
    return 0;
}

void SinglyLinkedListElementPrint(SinglyLinkedListElement *element){
    printf("\nsingly-linked list element with tag %d has data: ",element->tag);
    float *data = (element->data);
    printf("%.1f",*data);
    printf("\t");
}

void SinglyLinkedListNodeDestroy(SinglyLinkedListElement *toDestroy){
    toDestroy->next = NULL;
    toDestroy->tag = -1;
    toDestroy->data = NULL;
    free(toDestroy);
}

SinglyLinkedList* SinglyLinkedListCreate(){
    SinglyLinkedList *list = (SinglyLinkedList *)malloc(sizeof(SinglyLinkedList));
    list->length = 0;
    list->head = NULL;
    list->tail = NULL;
    return list;
}

SinglyLinkedListElement* SinglyLinkedListGetTail(SinglyLinkedList *list)
{
    SinglyLinkedListElement *element = list->head;
    while (element->next) {
        element = element->next;
    }
    
    return element;
}

void SinglyLinkedListInsertElement(SinglyLinkedList *list, SinglyLinkedListElement *toInsert, void* data){
    
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
}

SinglyLinkedListElement* SinglyLinkedListFindElement(SinglyLinkedList *list, SinglyLinkedListElement *toFind)
{
    SinglyLinkedListElement *element = list->head;
    
    while (element) {
        if (SinglyLinkedListElementCompare(element, toFind)){
            break;
        }
        
        element = element->next;
    }
    
    return element;
}

void SinglyLinkedListDeleteElement(SinglyLinkedList *list, SinglyLinkedListElement *toDelete){
    
}

void SinglyLinkedListPrint(SinglyLinkedList *list)
{
    SinglyLinkedListElement *element = list->head;
    while (element) {
        SinglyLinkedListElementPrint(element);
        element = element->next;
    }
    
}

void SinglyLinkedListDestroy(SinglyLinkedList *list)
{
    while (list->tail) {
        SinglyLinkedListDeleteElement(list, list->tail);
    }
    
    free(list);
}

@end
