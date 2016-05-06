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

int ListRemoveLast(List *l){
    if (l->n == 0 || l->head == NULL){
        return EMPTY;
    }
    
    if (l->tail == NULL){
        l->head = NULL;
        l->n--;
        return 0;
    }
    
    Item *this = l->head;
    
    while (this->next->next) {
        this = this->next;
    }
    
    this->next = NULL;
    l->tail = this;
    l->n--;
    return 0;
}

int ListRemoveFirst(List *l){
    if (l->n == 0 || l->head == NULL){
        return EMPTY;
    }
    if (l->n == 1){
        l->head = NULL;
        l->n--;
        return 0;
    }
    if (l->n == 2){
        Item *h = l->head;
        Item *t = h->next;
        Item **pos = &l->head;
        *pos = t;
        l->tail = NULL;
        l->n--;
        return 0;
    }
    
    Item **pos = &l->head;
    Item *h = l->head;
    Item *nh = h->next;
    h->next = NULL;
    *pos = nh;
    l->n--;
    return 0;
}

Item * ListLast(List *l){
    if (l->tail) return l->tail;
    if (l->head) return l->head;
    return NULL;
}

#define Stack List

#define StackCreate()       ListCreate()
#define StackPush(s,i)      ListAppendItem(s,i)
#define StackPop(s)         ListRemoveLast(s)
#define StackPeek(s)        ListLast(s)
#define StackIsEmpty(s)     ((s)->n <= 0) ? 1 : 0


#define Queue List

#define QueueCreate()       ListCreate()
#define QueueEnqueue(q,i)   ListAppendItem(q,i)
#define QueueDequeue(q)     ListRemoveFirst(q)
#define QueuePeek(q)        ((q)->n > 0) ? ((q)->head) : NULL
#define QueueIsEmpty        ((q)->n <= 0) ? 1 : 0

typedef struct Vertex_{
    int pos;
    int distance;
    int discovered;
    int processed;
    struct Vertex_ *next;
}Vertex;

Vertex* VertexCreate(){
    
    Vertex *v = (Vertex *)malloc(sizeof(Vertex));
    v->pos = 0;
    v->distance = 0;
    v->next = NULL;
    v->discovered = 0;
    v->processed = 0;
    return v;
}

#define ItemData(i)   (Vertex*)(i->data)

int VertexCompare(Vertex *a, Vertex *b){
    return (a->pos)-(b->pos);
}

void VertexSetNext(Vertex *v, Vertex *n){
    Vertex **pos = &v->next;
    *pos = n;
}

typedef struct Graph_{
    int size;
    Vertex *start;
    Vertex *end;
}Graph;

Graph* GraphCreate(){
    Graph *g = (Graph *)malloc(sizeof(Graph));
    g->size = 0;
    g->start = NULL;
    g->end = NULL;
    return g;
}

void GraphSetStart(Graph *g, Vertex *v){
    Vertex **pos = &g->start;
    *pos = v;
    g->size++;
}

void GraphSetEnd(Graph *g, Vertex *v){
    Vertex **pos = &g->end;
    *pos = v;
    g->size++;
}

Graph* GraphCreateDefault(){
    Graph *g = GraphCreate();
    Vertex *sv = VertexCreate();
    sv->pos = 1;
    GraphSetStart(g, sv);
    Vertex *ev = VertexCreate();
    ev->pos = 100;
    GraphSetEnd(g, ev);
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
            printf("LADDER %d - %d\n",start,end);
#endif
            ladders[end-1] = start-1;
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
            printf("SNAKE %d - %d\n",start,end);
#endif
            snakes[start-1] = end-1;
        }
        
        Graph *g = GraphCreateDefault();
        
        int spos = 0;
        int epos = 99;
        int pos = epos;
        int steps = 0;
        int rolls = 0;
        while (pos > spos) {
            
            if (ladders[pos] && ladders[pos] != pos){
                int ppos = pos;
                pos = ladders[ppos];
                int psteps = steps;
                if (psteps) {
                    rolls++;
                    steps = 0;
                }
                printf("after %d steps (%d rolls), took ladder from %d to %d\n",psteps,rolls,ppos+1,pos+1);
            }else{
                int ppos = pos;
                pos--;
                steps++;
                int psteps = steps;
                if (steps/6 == 1) {
                    rolls++;
                    steps = 0;
                }
                printf("walked from %d to %d. %d steps, %d rolls\n",ppos+1,pos+1,psteps,rolls);
            }
            
        }
        
        if (steps) rolls++;
        
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
