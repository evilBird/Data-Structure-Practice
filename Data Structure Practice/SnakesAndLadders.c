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

#define MAXV 100

typedef struct EdgeNode_{
    int d;
    int w;
    int x;
    int y;
    int visits;
    struct EdgeNode_ *next;
}EdgeNode;

EdgeNode * EdgeNodeCreate(int x, int y){
    EdgeNode *e = (EdgeNode *)malloc(sizeof(EdgeNode));
    e->x = x;
    e->y = y;
    e->w = y-x;
    e->visits = 0;
    e->next = NULL;
    e->d = 0;
    return e;
}

typedef struct Graph_{
    
    EdgeNode *edges[MAXV+1];
    int degrees[MAXV+1];
    int nvertices;
    int nedges;
    int directed;

}Graph;


int GraphInsertEdge(Graph *g, int x, int y, int d){
    
    if ( x < 1 || x > MAXV || y < 1 || y > MAXV ) return -1;
    int i = (x-1);
    EdgeNode *newNode, **pos;
    newNode = EdgeNodeCreate(x, y);
    newNode->d = d;
    if (g->edges[i] == NULL){
        pos = &g->edges[i];
    }else{
        EdgeNode *oldNode = g->edges[i];
        while (oldNode->next) {
            oldNode = oldNode->next;
        }
        pos = &oldNode->next;
    }
    
    *pos = newNode;
    
    g->degrees[i]++;
    g->nedges++;
    
    return 0;
}

Graph* GraphCreate(){
    
    Graph *g = (Graph *)malloc(sizeof(Graph));
    g->nvertices = MAXV;
    g->nedges = 0;
    g->directed = 0;
    memset(g->degrees, 0, sizeof(int)*MAXV);
    for (int i = 0; i < MAXV; i++) g->edges[i] = NULL;
    return g;
}

void EdgeNodePrint(EdgeNode *e){
    printf("\tEdge %d - %d (d = %d, w = %d)\n",e->x,e->y,e->d,e->w);
}

void GraphPrint(Graph *g){
    printf("GRAPH WITH %d VERTICES AND %d EDGES\n",g->nvertices,g->nedges);
    for (int i = 0; i < g->nvertices; i++) {
        if (g->degrees[i]){
            printf("vert %d (deg=%d):\n",i+1,g->degrees[i]);
            EdgeNode *edge = NULL;
            for (int j = 0; j < g->degrees[i]; j++){
                if (!edge){
                    edge = g->edges[i];
                }else{
                    edge = edge->next;
                }
                
                EdgeNodePrint(edge);
            }
        }
    }
    printf("\n");
}

void GraphFindEdgeNode(Graph *g, int x, int *next){
    
    int n = x+1;
    *next = -1;
    
    while (n <= g->nvertices) {
        
        if (g->degrees[n-1] == 0){
            
            n++;
            
        }else{
            
            *next = n;
            break;
        }
    }
    
    if (n >= g->nvertices){
        
        *next = 100;
        
    }
}

#define HUGE_VALUE 100000000
#define DICE_NSIDES 6

void IncrementDice(int *dist, int *flag){
    *dist += 1;
    if (*dist > DICE_NSIDES) *flag = 1;
    else *flag = 0;
}

void RollDice(int *dist, int *rolls){
    
    *rolls += 1;
    *dist = 1;
}

int GraphTraverseDF(Graph *g, int x, int *visits, int dist, int rolls, int *curmin){
    
    if (visits[x-1] > 0 || (*curmin > 0 && rolls > *curmin)){
        free(visits);
        return -1;
    }
    
    if (x == g->nvertices){
        
        //if (dist) rolls++;
        if (*curmin == -1 || rolls < *curmin){
            *curmin = rolls;
            //printf("\n\t*SUCCESS* @ x = 100 dist = %d rolls = %d\n\n",dist,rolls);
        }
        printf("\n\t*SUCCESS* @ x = 100 dist = %d rolls = %d min = %d\n\n",dist,rolls,*curmin);

        free(visits);
        return rolls;
    }
    
    visits[x-1] += 1;
    
    printf("SEARCH @ x = %d deg = %d visits = %d dist = %d rolls = %d\n",x,g->degrees[x-1],visits[x-1],dist,rolls);
    
    int min,retval;
    EdgeNode *e;
    
    min = HUGE_VALUE;
    retval = -1;
    
    e = ( g->degrees[x-1] > 0) ? ( g->edges[x-1] ) : NULL;
    
    if (!e || visits[x] > 0) {
        int flag;
        IncrementDice(&dist, &flag);
        if (flag) RollDice(&dist, &rolls);
        return GraphTraverseDF(g, x+1, visits, dist, rolls, curmin);
        
    }else{
        visits[x] = 1;
        
        for (int i = 0; i < g->degrees[x-1]; i++) {
            
            int myDist = dist;
            int myRolls = rolls;
            
            for (int j = 0; j < e->d; j++){
                int flag;
                IncrementDice(&myDist, &flag);
                if (flag) RollDice(&myDist, &myRolls);
            }
            
            int *myVisits = (int*)malloc(sizeof(int) * g->nvertices + 1);
            memcpy(myVisits, visits, sizeof(int) * g->nvertices + 1);
            retval = GraphTraverseDF(g, e->y, myVisits, myDist, myRolls, curmin);
            if ( retval != -1 && retval < min) min = retval;
            
            e = (e->next) ? (e->next) : NULL;
            
            if (min == HUGE_VALUE){
                min = -1;
            }
            
        }

    }
    if (min == HUGE_VALUE) min = -1;
    return min;

}

int GraphSearch(Graph *g, int x, int steps, int rolls){
    
    return 0;
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
        
        Graph *graph = GraphCreate();
        
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
            if (start > 0){
                
                GraphInsertEdge(graph, start-1, end, 1);
                
                if (start < (graph->nvertices)){
                    GraphInsertEdge(graph, start-1, start+1, 2);
                }
            }
        }
        

        
        int M;
#ifndef XCODE_TEST_RUN
        scanf("%d",&M);
#else
        sscanf(input+in_bytes_consumed, "%d%n",&M,&in_bytes_now);
        in_bytes_consumed+=in_bytes_now;
#endif
        
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
            if (start > 0){
                
                GraphInsertEdge(graph, start-1, end, 1);
                
                if (start < (graph->nvertices)){
                    GraphInsertEdge(graph, start-1, start+1, 2);
                }
            }
        }
        

#ifdef XCODE_TEST_DEBUG
        GraphPrint(graph);
#endif
        int *visits = (int*)(malloc(sizeof(int) * graph->nvertices+1));
        memset(visits, 0, sizeof(int) * graph->nvertices+1);
        int min = -1;
        int rolls = 1;
        int dist = 1;
        GraphTraverseDF(graph, 1, visits, dist, rolls, &min);
        
        
#ifndef XCODE_TEST_RUN
        printf("%d\n",min);
#else
        printf("%d\n",min);
        
        if (t){
            out_bytes_now = sprintf(output+out_bytes_consumed,"\n");
            out_bytes_consumed+=out_bytes_now;
        }
        
        out_bytes_now = sprintf(output+out_bytes_consumed, "%d",min);
        out_bytes_consumed+=out_bytes_now;
        
#endif
        
    }
    return 0;
}
