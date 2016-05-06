//
//  SnakesAndLadders.c
//  Data Structure Practice
//
//  Created by Travis Henspeter on 5/4/16.
//  Copyright © 2016 birdSound. All rights reserved.
//

#include "SnakesAndLadders.h"
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

#define EMPTY -1

typedef struct Item_{
    void *data;
    struct Item_ *next;
}Item;

Item * ItemCreate(void *data){
    Item *item = (Item*)malloc(sizeof(Item));
    item->data = NULL;
    item->next = NULL;
    void **ptr = &item->data;
    *ptr = data;
    return item;
}


typedef struct List_{
    int n;
    Item *head;
    Item *tail;
}List;


List * ListCreate(){
    List *list = (List *)malloc(sizeof(List));
    list->n = 0;
    list->head = NULL;
    list->tail = NULL;
    return list;
}

void ListAppendItem(List *l, Item *i){
    Item **pos;
    if (l->head == NULL){
        pos = &l->head;
        *pos = i;
        l->n++;
    }else if (l->tail == NULL){
        pos = &l->head->next;
        *pos = i;
        l->tail = i;
        l->n++;
    }else{
        pos = &l->tail->next;
        *pos = i;
        l->tail = i;
        l->n++;
    }
}

void ListAppend(List *l, void *data){
    Item *item = ItemCreate(data);
    ListAppendItem(l, item);
}

int ListRemoveLast(List *l, void **data){
    
    if (l->n == 0 || l->head == NULL){
        if (data) *data = NULL;
        return EMPTY;
    }
    
    Item *this = l->head;
    Item **newTail = &l->tail;
    Item **newHead = &l->head;
    
    if (l->tail == NULL){
        *newHead = NULL;
        l->n = 0;
        if (data) *data = this->data;
        return 0;
    }
    
    Item *that = NULL;
    
    while (this->next) {
        that = this->next;
        if (that->next == NULL) break;
        this = that;
    }
    
    if (data) *data = that->data;
    this->next = NULL;
    *newTail = this;
    l->n--;
    return 0;
}

int ListRemoveFirst(List *l, void **data){
    
    if (l->n == 0 || l->head == NULL){
        if (data) *data = NULL;
        return EMPTY;
    }
    
    Item *this = l->head;
    Item **newHead = &l->head;
    if (data) {
        *data = this->data;
    }
    
    if (!this->next){
        *newHead = NULL;
        l->n = 0;
        return 0;
    }
    
    
    Item *that = this->next;
    *newHead = that;
    Item **newTail = &l->tail;
    
    if (!that->next){
        *newTail = NULL;
        l->n = 1;
        return 0;
    }else{
        Item *next = that->next;
        *newTail = next;
        l->n--;
        return 0;
    }
}

int ListFirstData(List *l, void **data){
    Item *first;
    if (l->n == 0 || l->head == NULL){
        if (data) *data = NULL;
        return EMPTY;
    }
    
    first = l->head;
    if (data) *data = first->data;
    return 0;
}

int ListLastData(List *l, void **data){
    Item *last;
    if (l->n == 0){
        if (data) *data = NULL;
        return EMPTY;
    }
    
    if (l->tail) last = l->tail;
    else last = l->head;
    
    if (data) *data = last->data;
    
    return 0;
}

#define Stack List

#define StackCreate()       ListCreate()
#define StackPush(s,d)      ListAppend(s,d)
#define StackPop(s,d)       ListRemoveLast(s,d)
#define StackPeek(s,d)      ListLastData(s,d)
#define StackIsEmpty(s)     (((s)->n == 0) ? 1 : 0)

#define Queue List

#define QueueCreate()       ListCreate()
#define QueueEnqueue(q,d)   ListAppend(q,d)
#define QueueDequeue(q,d)   ListRemoveFirst(q,d)
#define QueuePeek(q,d)      ListFirstData(q,d)
#define QueueIsEmpty(q)     (((q)->n == 0) ? 1 : 0)


void PrintList(List *list){
    printf("List n = %d\n",list->n);
    if (list->head == NULL || list->n == 0) return;
    Item *item = list->head;
    printf("%d ",(*(int*)item->data));
    for (int i = 1; i < list->n; i ++) {
        item = item->next;
        printf("%d ",(*(int*)item->data));
    }
    printf("\n");
}

#define PrintStack(s)   PrintList(s)

static void TestList(){
    printf("TEST LIST\n");
    List *list = ListCreate();
    int arr[11];
    printf("TEST LIST APPEND\n");
    for (int i = 0; i < 10; i ++) {
        arr[i] = i;
        ListAppend(list, &arr[i]);
        PrintList(list);
    }
    printf("TEST LIST REMOVE LAST\n");
    for (int i = 0; i < 5; i++) {
        ListRemoveLast(list,NULL);
        PrintList(list);
    }
    printf("TEST LIST REMOVE FIRST\n");
    for (int i = 0; i < 5; i++) {
        ListRemoveFirst(list,NULL);
        PrintList(list);
    }
}

static void TestStack(){
    printf("TEST STACK\n");
    Stack *stack = StackCreate();
    int arr[11];
    printf("TEST STACK PUSH\n");
    for (int i = 0; i < 10; i ++) {
        arr[i] = i;
        StackPush(stack, &arr[i]);
        PrintStack(stack);
    }
    printf("TEST STACK POP\n");
    for (int i = 0; i < 10; i++) {
        StackPop(stack,NULL);
        PrintStack(stack);
    }
}

void TestStructs(){
    TestList();
    TestStack();
}

typedef struct Vertex_{
    int pos;
    int distance;
    int discovered;
    int processed;
    List *adjacent;
    struct Vertex_ *parent;
}Vertex;

Vertex* VertexCreate(){
    
    Vertex *v = (Vertex *)malloc(sizeof(Vertex));
    v->pos = 0;
    v->distance = 0;
    v->adjacent = ListCreate();
    v->discovered = 0;
    v->processed = 0;
    v->parent = NULL;
    return v;
}

#define ItemData(i)   (Vertex*)(i->data)

int VertexCompare(Vertex *a, Vertex *b){
    return (a->pos)-(b->pos);
}

typedef struct Graph_{
    int size;
    Vertex *vertices[101];
    Queue  *toProcess;
}Graph;

Graph* GraphCreate(){
    Graph *g = (Graph *)malloc(sizeof(Graph));
    g->size = 0;
    g->toProcess = QueueCreate();
    memset(g->vertices, 0, sizeof(Vertex*)*100);
    return g;
}

void GraphPrint(Graph *g){
    int n = g->size;
    printf("GRAPH SIZE %d\n",n);
    for (int i = 0; i < n; i++) {
        Vertex *v = g->vertices[i];
        if (v){
            printf("%d) vertex pos %d discovered %d processed %d neighbors %d\n",i,v->pos,v->discovered,v->processed,v->adjacent->n);
        }
    }
    printf("\n");
}

void GetPathInfo(Graph *graph, Vertex *vertex, int *rolls, int *steps){
    
    if ( vertex->parent ){
        
        int mpos = vertex->pos;
        int ppos = vertex->parent->pos;
        
        if (abs(mpos-ppos) > 1){
            *steps = 0;
            *rolls += 1;
        }else{
            *steps += 1;
            if (*steps == 6){
                *rolls += 1;
                *steps = 0;
            }
        }
        
        GetPathInfo(graph, vertex->parent, rolls, steps);
        
    }else{
        
        if (*steps > 0){
            *rolls += 1;
        }
        
    }
    
}

void ProcessVertex(Graph *graph, Vertex *vertex, void *toFind, int *numRolls){
    
    if (vertex == NULL) return;
    if (vertex->processed == 1) return;
    vertex->processed = 1;
#ifdef XCODE_TEST_DEBUG
    printf("processing vertex at pos %d\n",vertex->pos);
#endif
    if (vertex->pos == (*(int*)toFind)) {
        
#ifdef XCODE_TEST_DEBUG
        printf("found search target vertex at pos %d\n",vertex->pos);
#endif
        
        int curMin = *numRolls;
        int thisMin = 0;
        int steps = 0;
        //GetPathInfo(graph, vertex, &thisMin, &steps);
        
        if (thisMin > 0){
            if (curMin == 0){
                curMin = thisMin;
            }else if (thisMin < curMin){
                curMin = thisMin;
            }
            *numRolls = curMin;
        }
    }
}

void ProcessQueue(Graph *graph, void *toFind, int *numRolls){
    
    while (QueueIsEmpty(graph->toProcess) == 0) {
        Vertex **toProcess;
        QueueDequeue(graph->toProcess, (void**)toProcess);
        ProcessVertex(graph, *toProcess, toFind, numRolls);
    }
}

void GraphBFS(Graph *graph, Vertex *vertex, void *toFind, int *numRolls){
    
    if (vertex == NULL){
        return;
    }
    
    if (vertex->discovered == 0){
        vertex->discovered = 1;
#ifdef XCODE_TEST_DEBUG
        printf("discovered vertex at pos %d\n",vertex->pos);
#endif
        if (vertex->processed == 0) {
            QueueEnqueue(graph->toProcess, vertex);
        }
        
        while (QueueIsEmpty(graph->toProcess) == 0) {
            Vertex **toProcess;
            QueueDequeue(graph->toProcess, (void**)toProcess);
            ProcessVertex(graph, *toProcess, toFind, numRolls);
        }
    }

    
    if (vertex->adjacent->n == 0) return;
    
    Item *item = vertex->adjacent->head;
    
    printf("Vertex pos %d will search %d neighbors\n",vertex->pos,vertex->adjacent->n);
    int numSearched = 0;
    
    while (numSearched < vertex->adjacent->n) {
        
        Vertex *adjacent = (Vertex*)item->data;
        printf("Vertex pos %d, searching neighbor at pos %d (%d of %d)\n",vertex->pos,adjacent->pos,(numSearched+1),vertex->adjacent->n);
        
        if (adjacent->discovered == 0){
            GraphBFS(graph, adjacent, toFind,numRolls);
        }
        
        if (!(item->next)){
            break;
        }
        
        numSearched++;
        item = item->next;
    }
}

Graph * GraphCreateWithLaddersAndSnakes(int *ladders, int *snakes, int n){
    Graph *g = GraphCreate();
    
    for (int i = 0; i<n; i++) {
        
        int pos = (i+1);
        Vertex **vertex = &g->vertices[i];
        
        if (*vertex == NULL){
            *vertex = VertexCreate();
            (*vertex)->pos = pos;
            (*vertex)->distance = 1;
            g->size++;
        }
        
        if (i){
            Vertex *prev = g->vertices[i-1];
            ListAppend(prev->adjacent, (*vertex));
            Vertex **parent = &(*vertex)->parent;
            if (!*parent) *parent = prev;
        }

        int npos = -1;
        
        if (ladders[i] != 0){
            npos = ladders[i];
        }else if (snakes[i] != 0){
            npos = snakes[i];
        }
        
        if (npos >= 0 && npos < 100){
            
            Vertex **nvert = &g->vertices[npos];
            
            if (*nvert == NULL){
                *nvert = VertexCreate();
                (*nvert)->pos = (npos+1);
                (*nvert)->distance = 1;
                g->size++;
            }
            
            Vertex **npar = &(*nvert)->parent;
            
            if (*npar == NULL){
                *npar = *vertex;
            }
            
            ListAppend((*vertex)->adjacent, *nvert);
            
        }
        
    }
    
    return g;
}

#ifdef XCODE_TEST_RUN
int SnakesAndLaddersRunTestCase(char *output, const char *input)
#else
int main()
#endif
{
    int T;
#ifndef XCODE_TEST_RUN
    scanf("%d",&T);
#else
    int in_bytes_consumed = 0, in_bytes_now = 0;
    int out_bytes_consumed = 0, out_bytes_now = 0;
    sscanf(input, "%d%n",&T,&in_bytes_now);
    in_bytes_consumed+=in_bytes_now;
    
#endif

    for (int t = 0; t < T; t++){
        int N;
        
        
#ifndef XCODE_TEST_RUN
        scanf("%d",&N);
#else
        sscanf(input+in_bytes_consumed,"%d%n",&N,&in_bytes_now);
        in_bytes_consumed+=in_bytes_now;
#endif
        int ladders[101];
        memset(ladders,0,sizeof(int)*100);
        
        for (int n = 0; n < N; n++){
            int start,end;
#ifndef XCODE_TEST_RUN
            scanf("%d %d",&start,&end);
#else
            sscanf(input+in_bytes_consumed,"%d %d%n",&start,&end,&in_bytes_now);
            in_bytes_consumed+=in_bytes_now;
#ifdef XCODE_TEST_DEBUG
            printf("LADDER %d - %d\n",start,end);
#endif
            
#endif
            ladders[start-1] = end-1;
        }
        
        int M;
#ifndef XCODE_TEST_RUN
        scanf("%d",&M);
#else
        sscanf(input+in_bytes_consumed, "%d%n",&M,&in_bytes_now);
        in_bytes_consumed+=in_bytes_now;
#endif
        int snakes[101];
        memset(snakes, 0, sizeof(int)*100);
        
        for (int m = 0; m < M; m++){
            int start,end;
#ifndef XCODE_TEST_RUN
            scanf("%d %d",&start,&end);
#else
            sscanf(input+in_bytes_consumed,"%d %d%n",&start,&end,&in_bytes_now);
            in_bytes_consumed+=in_bytes_now;
#ifdef XCODE_TEST_DEBUG
            printf("SNAKE %d - %d\n",start,end);
#endif
            
#endif
            snakes[start-1] = end-1;
        }
        

        int rolls = 0;
        int steps = 0;
        Graph *myGraph = GraphCreateWithLaddersAndSnakes(ladders, snakes, 100);
#ifdef XCODE_TEST_DEBUG
        GraphPrint(myGraph);
#endif
        int endPos = 100;
        GraphBFS(myGraph, myGraph->vertices[0], (void*)&endPos, &rolls);
        
        
        
#ifdef XCODE_TEST_DEBUG
        GraphPrint(myGraph);
#endif
        
#ifndef XCODE_TEST_RUN
        printf("%d\n",rolls);
#else
        printf("%d\n",rolls);
        
        if (t){
            out_bytes_now = sprintf(output+out_bytes_consumed,"\n");
            out_bytes_consumed+=out_bytes_now;
        }
        
        out_bytes_now = sprintf(output+out_bytes_consumed, "%d",rolls);
        out_bytes_consumed+=out_bytes_now;
        
#endif
        
    }
    return 0;
}
