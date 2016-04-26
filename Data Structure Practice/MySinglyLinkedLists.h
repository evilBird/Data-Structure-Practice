//
//  MyLinkedLists.h
//  Data Structure Practice
//
//  Created by Travis Henspeter on 4/5/16.
//  Copyright © 2016 birdSound. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "MyDataStructureUtils.h"

#define sll                 SinglyLinkedList
#define sll_elem            SinglyLinkedListElement
#define sll_init            SinglyLinkedListCreate
#define sll_append          SinglyLinkedListAppend
#define sll_search          SinglyLinkedListSearchWithMatchFunction
#define sll_insert_next     SinglyLinkedListInsertNext
#define sll_remove_next     SinglyLinkedListRemoveNext
#define sll_destroy         SinglyLinkedListDestroy
#define rand_float          GetRandomFloat
#define rand_float_b        GetRandomFloatInRange
#define match_float         MyFloatMatchFunction

float GetRandomFloatInRange(int loc, int length);
float GetRandomFloat();
float RandomFloatInRange(float min, float max);

@interface MySinglyLinkedLists : NSObject

typedef struct MySinglyLinkedListElement{
    
    void                                *data;
    struct MySinglyLinkedListElement    *next;
    
}SinglyLinkedListElement;

SinglyLinkedListElement* SinglyLinkedListElementCreate();

int MyFloatMatchFunction(const void *key1, const void *key2);
int MatchIntegersFunction(const void *key1, const void *key2);
void SinglyLinkedListElementPrint(SinglyLinkedListElement *element);

typedef struct MySinglyLinkedList{
    
    SinglyLinkedListElement              *head;
    SinglyLinkedListElement              *tail;
    int                                  count;
    int                                  (*match)(const void *key1, const void *key2);
    
}SinglyLinkedList;

SinglyLinkedList* SinglyLinkedListCreate(int (*match)(const void *key1, const void *key2));

int SinglyLinkedListCountElements(SinglyLinkedList *list);

SinglyLinkedListElement* SinglyLinkedListSearchWithMatchFunction(SinglyLinkedList *list,
                                                                 int (*match)(const void* key1, const void* key2),
                                                                 void* toFind);

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

void FormatFloatData(char *result, const void *data);

void FormatIntegerData(char *result, const void *data);

void SinglyLinkedListPrintVisual(SinglyLinkedList *list, void (*formatData)(char *, const void *));

@end
