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
    list->count = 0;
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

int SinglyLinkedListInsertNext(SinglyLinkedList *list, SinglyLinkedListElement *element, void *toInsert)
{
    SinglyLinkedListElement *new = NULL;
    new = SinglyLinkedListElementCreate();
    
    if (!new) {
        return -1;
    }
    
    new->data = (void*)toInsert;
    
    if (!element) {
        
        if (list->count == 0) {
            list->tail = new;
            new->next = list->head;
            list->head = new;
        }
        
    }else{
        if (!element->next) {
            list->tail = new;
        }
        
        new->next = element->next;
        element->next = new;
    }
    
    list->count++;
    
    return 0;
    
}

int SinglyLinkedListInsertNextData(SinglyLinkedList *list, void *toFind, void *toInsert){
    
    SinglyLinkedListElement *found = NULL;
    found = SinglyLinkedListSearch(list, toFind);
    return SinglyLinkedListInsertNext(list, found, toInsert);
}


int SinglyLinkedListAppend(SinglyLinkedList *list, void* data){
    if (list->count) {
        return SinglyLinkedListInsertNext(list, list->tail, data);
    }else{
        return SinglyLinkedListInsertNext(list, NULL, data);
    }
}

int SinglyLinkedListRemoveNext(SinglyLinkedList *list, SinglyLinkedListElement *element, void **data){
    
    SinglyLinkedListElement *toDestroy = NULL;
    
    if (!element) {
        
        if (!list->head) {
            return -1;
        }
        
        if (data) {
            *data = list->head->data;
        }
        
        toDestroy = list->head;
        list->head = list->head->next;
        
        if (list->count==1) {
            list->tail = NULL;
        }
        
    }else if (element->next){
        
        if (data) {
            *data = element->next->data;
        }
        
        toDestroy = element->next;
        element->next = element->next->next;
        
        if (!element->next) {
            list->tail = element;
        }
        
    }
    
    if (toDestroy) {
        free(toDestroy);
    }
    
    list->count--;
    
    return 0;
}

int SinglyLinkedListRemoveNextData(SinglyLinkedList *list, void *toFind, void **data){
    
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
    while (list->count) {
        if (SinglyLinkedListRemoveNext(list, NULL, NULL) != 0) {
            break;
        }
    }
    
    list->head = NULL;
    list->tail = NULL;
    free(list);
}

@end
