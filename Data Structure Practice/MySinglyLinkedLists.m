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
    element->data = NULL;
    return element;
}

void SinglyLinkedListElementPrint(SinglyLinkedListElement *element){
    printf("\nsingly-linked list element has data: ");
    printf("%.f",(*(float *)(element->data)));
    printf("\t");
}

void SinglyLinkedListElementDestroy(SinglyLinkedListElement *toDestroy){
    toDestroy->next = NULL;
    toDestroy->data = NULL;
    free(toDestroy);
}

SinglyLinkedList* SinglyLinkedListCreate(){
    
    SinglyLinkedList *list = (SinglyLinkedList *)malloc(sizeof(SinglyLinkedList));
    list->head = NULL;
    list->tail = NULL;
    return list;
}

int SinglyLinkedListCountElements(SinglyLinkedList *list)
{
    int count = 0;
    SinglyLinkedListElement *element = list->head;
    
    while (element->next) {
        count++;
        element = element->next;
    }
    
    return count;
}

SinglyLinkedListElement* SinglyLinkedListSearch(SinglyLinkedList *list, void *toFind)
{
    SinglyLinkedListElement *result = NULL;
    SinglyLinkedListElement *element = list->head;
    
    while (element) {
        if (*((float *)(element->data)) == *((float *)toFind)) {
            result = element;
            break;
        }
        
        element = element->next;
    }
    
    return result;
}

void SinglyLinkedListInsertNext(SinglyLinkedList *list, SinglyLinkedListElement *element, void *toInsert)
{
    SinglyLinkedListElement *new = SinglyLinkedListElementCreate();
    new->data = (void*)toInsert;
    
    if (!element) {
        
        if (list->head) {
            new->next = list->head;
        }
        
        list->head = new;
        if (!list->tail) {
            list->tail = list->head;
        }
        return;
    }
    
    new->next = element->next;
    element->next = new;
    if (!new->next) {
        list->tail = new;
    }
}

void SinglyLinkedListInsertNextData(SinglyLinkedList *list, void *toFind, void *toInsert){
    
    SinglyLinkedListElement *found = NULL;
    found = SinglyLinkedListSearch(list, toFind);
    SinglyLinkedListInsertNext(list, found, toInsert);
}


void SinglyLinkedListAppend(SinglyLinkedList *list, void* data){
    
    if (list->tail) {
        return SinglyLinkedListInsertNext(list, list->tail, data);
    }else{
        return SinglyLinkedListInsertNext(list, NULL, data);
    }
}

void SinglyLinkedListRemoveNext(SinglyLinkedList *list, SinglyLinkedListElement *element, void **data){
    
    if (!element) {
        
        if (!list->head) {
            if (*data) {
                *data = NULL;
            }
            return;
        }
        
        SinglyLinkedListElement *toDestroy = list->head;
        
        if (*data) {
            *data = toDestroy->data;
        }
        
        list->head = toDestroy->next;
        SinglyLinkedListElementDestroy(toDestroy);
        
        return;
    }
    
    SinglyLinkedListElement *toDestroy = element->next;
    
    if (!toDestroy) {
        return;
    }
    
    if (toDestroy->next) {
        element->next = toDestroy->next;
    }
    
    if (data) {
        *data = toDestroy->data;
    }
    
    SinglyLinkedListElementDestroy(toDestroy);
    
}

void SinglyLinkedListRemoveNextData(SinglyLinkedList *list, void *toFind, void **data){
    
    SinglyLinkedListElement *found = SinglyLinkedListSearch(list, toFind);
    return SinglyLinkedListRemoveNext(list, found, data);
}

void SinglyLinkedListPrint(SinglyLinkedList *list)
{
    SinglyLinkedListElement *element = list->head;
    
    while (element) {
        SinglyLinkedListElementPrint(element);
        element = element->next;
    }
    
    printf("\n");
}

void SinglyLinkedListDestroy(SinglyLinkedList *list)
{
    SinglyLinkedListElement *head = list->head;
    SinglyLinkedListElement *element = head;
    while (element->next) {
        SinglyLinkedListElement *toDestroy = element->next;
        SinglyLinkedListElement *newNext = toDestroy->next;
        SinglyLinkedListRemoveNext(list, element, NULL);
        element = head;
        if (newNext) {
            element->next = newNext;
        }
    }
    
    SinglyLinkedListElementDestroy(head);
    list->head = NULL;
    list->tail = NULL;
    free(list);
}

@end
