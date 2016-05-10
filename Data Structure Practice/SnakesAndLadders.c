//
//  SnakesAndLadders.c
//  Data Structure Practice
//
//  Created by Travis Henspeter on 5/4/16.
//  Copyright © 2016 birdSound. All rights reserved.
//

#include "SnakesAndLadders.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


#define MAXV 100
#define ERR -1
#define MAXINT 100000000
#define NSIDES 6

#define ALLOCATE(name)      ((name*)(malloc(sizeof(name))))
#define VertIndex(v)        (((v)->x) - 1)
#define EdgeIndex(e)        (((e)->x) - 1)
#define EdgeIsLadder(e)     ((((e)->y - (e)->x) > 1 ) ? 1 : 0)
#define EdgeIsSnake(e)      ((((e)->x - (e)->y) > 1 ) ? 1 : 0)
#define ResetDice(e)        ((( EdgeIsLadder(e) || EdgeIsSnake (e) ) == 1) ? 1 : 0)

typedef struct Edge_{
    int x;
    int y;
    int w;
    struct Edge_ *next;
}Edge;

void InitializeEdge(Edge *e){
    e->x = 0;
    e->y = 0;
    e->w = 0;
    e->next = NULL;
}

Edge * NewEdge(){
    Edge *e = ALLOCATE(Edge);
    InitializeEdge(e);
    return e;
}

Edge * CreateNewEdge(int x, int y, int w){
    Edge *e = NewEdge();
    e->x = x;
    e->y = y;
    e->w = w;
    return e;
}

void PrintEdge(Edge *e){
    
    printf("\tEdge %d - %d (w = %d)\n",e->x,e->y,e->w);
}

typedef struct Vertex_{
    int x;
    int discovered;
    int processed;
    int parent;
}Vertex;


void InitializeVertex(Vertex *v){
    v->x = 0;
    v->discovered = 0;
    v->processed = 0;
    v->parent = 0;
}

Vertex * NewVertex(){
    Vertex *v = ALLOCATE(Vertex);
    InitializeVertex(v);
    return v;
}

typedef struct VertexQueue_{
    int n;
    Vertex *vertices[MAXV+1];
}VertexQueue;

void InitializeVertexQueue(VertexQueue *vq){
    vq->n = 0;
    for (int i = 0; i < MAXV + 1; i ++) vq->vertices[i] = NULL;
}

VertexQueue * NewVertexQueue(){
    VertexQueue *vq = ALLOCATE(VertexQueue);
    InitializeVertexQueue(vq);
    return vq;
}

int VertexQueueIsEmpty(VertexQueue *vq){
    return ((vq->n > 0) ? 0 : 1);
}

void PrintVertex(Vertex *v){
    printf("Vertex x = %d discovered = %d processed = %d parent = %d\n",v->x,v->discovered,v->processed,v->parent);
}

void EnqueueVertex(VertexQueue *vq, Vertex *v){
    vq->vertices[vq->n] = v;
    vq->n++;
}

Vertex *DequeueVertex(VertexQueue *vq){
    
    if (vq->n == 0){
        return NULL;
    }
    
    Vertex *result = vq->vertices[0];
    for (int i = 1; i < vq->n; i++) vq->vertices[i-1] = vq->vertices[i];
    vq->n--;
    return result;
}

#define VertexStack         VertexQueue
#define NewVertexStack      NewVertexStack

void PushVertex(VertexStack *vs, Vertex *v){
    vs->vertices[vs->n] = v;
    vs->n++;
}

Vertex * PopVertex(VertexStack *vs){
    if (vs->n == 0){
        return NULL;
    }
    Vertex *result = vs->vertices[vs->n - 1];
    vs->n--;
    return result;
}

typedef struct Graph_{
    int nvertices;
    int nedges;
    int directed;
    int degrees[MAXV+1];
    Vertex *vertices[MAXV+1];
    Edge *edges[MAXV+1];
}Graph;


void InitializeGraph(Graph *g){
    
    g->nvertices = 0;
    g->nedges = 0;
    g->directed = 0;
    
    for (int i = 0; i < MAXV; i ++) g->degrees[i] = 0;
    for (int i = 0; i < MAXV; i ++) g->edges[i] = NULL;
    
    for (int i = 0; i < MAXV; i ++) {
        Vertex *v = NewVertex();
        v->x = (i + 1);
        Vertex **pos = &g->vertices[i];
        *pos = v;
        g->nvertices++;
    }
}

Graph * NewGraph(int directed){
    Graph *g = ALLOCATE(Graph);
    InitializeGraph(g);
    g->directed = directed;
    return g;
}

void InsertEdge(Graph *g, Edge *e){
    Edge *existing = ( g->degrees[EdgeIndex(e)] > 0 ) ? g->edges[EdgeIndex(e)] : NULL;
    
    if (!existing){
        g->edges[EdgeIndex(e)] = e;
    }else{
        while (existing) {
            
            if (existing->next){
                existing = existing->next;
            }else{
                break;
            }
        }
        
        existing->next = e;
    }
    g->degrees[EdgeIndex(e)] += 1;
    g->nedges++;
}

void PrintGraph(Graph *g){
    
    printf("\nGRAPH WITH %d VERTICES AND %d EDGES\n",g->nvertices,g->nedges);
    for (int i = 0; i < g->nvertices; i ++){
        
        PrintVertex(g->vertices[i]);
        
        if (g->degrees[i]){
            Edge *e = g->edges[i];
            while (e) {
                PrintEdge(e);
                if (e->next){
                    e = e->next;
                }else{
                    break;
                }
            }
        }
    }
    
    printf("\n");
}

void InsertSnakesAndLadders(Graph *g, int *ladders, int *snakes){
    
    int lastEmpty = 1;
    
    for (int x = 1; x < g->nvertices; x ++){
        
        if (ladders[x]){
            
            int y = ladders[x];
            Edge *ladder = CreateNewEdge(x, y, 0);
            InsertEdge(g, ladder);
            Edge *e = CreateNewEdge(lastEmpty, x, x-lastEmpty);
            InsertEdge(g, e);
            
        }else if (snakes[x]){
            
            int y = snakes[x];
            Edge *snake = CreateNewEdge(x, y, 0);
            InsertEdge(g, snake);
            Edge *e = CreateNewEdge(lastEmpty, x, x-lastEmpty);
            InsertEdge(g, e);
            
        }else{
            
            if (x > lastEmpty){
                Edge *e = CreateNewEdge(lastEmpty, x, x-lastEmpty);
                InsertEdge(g, e);
            }
            
            lastEmpty = x;
        }
    }
    
    Edge *e = CreateNewEdge(lastEmpty, g->nvertices, g->nvertices-lastEmpty);
    InsertEdge(g, e);
}

void InitializeSearch(Graph *g){
    for (int i = 0; i < g->nvertices; i++) {
        (g->vertices[i])->discovered = 0;
        (g->vertices[i])->processed = 0;
        (g->vertices[i])->parent = 0;
    }
}

void PrintPath(Graph *g, Vertex *v){
    int len = 0;
    int bw[MAXV+1];
    memset(bw,0,sizeof(int)*MAXV+1);
    bw[len] = v->x;
    len++;
    while (v->parent > 0) {
        Vertex *p = g->vertices[v->parent - 1];
        bw[len] = p->x;
        v = p;
        len++;
    }
    printf("\nPRINT PATH:\n");
    for (int i = 0; i < len; i++) {
        printf("%d ",bw[i]);
    }
    
    printf("\n");
}

void Swap(int *a, int *b){
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void ReversePath(int *path, int n){
    int i = 0;
    int j = n-1;
    while (i < j) {
        Swap(&path[i], &path[j]);
        i++;
        j--;
    }
}

int GetPath(Graph *g, Vertex *v, int *path){
    
    int n = 0;
    path[n] = v->x;
    n++;
    
    while (v->parent > 0) {
        Vertex *p = g->vertices[v->parent - 1];
        path[n] = p->x;
        v = p;
        n++;
    }
    
    ReversePath(path, n);
    return n;
}

void ProcessVertexEarly(Graph *g, Vertex *v){
#ifdef XCODE_TEST_DEBUG
    printf("Early Process Vertex %d\n",v->x);
    PrintVertex(v);
#endif
}

void ProcessVertexLate(Graph *g, Vertex *v){
#ifdef XCODE_TEST_DEBUG
    printf("Late Process Vertex %d\n",v->x);
    PrintVertex(v);
    if (v->x == 100){
        PrintPath(g, v);
    }
#endif
}

void ProcessEdge(Graph *g, Edge *e, Vertex *v){
#ifdef XCODE_TEST_DEBUG
    PrintEdge(e);
#endif
}

void GraphBFS(Graph *g, int start){
    
    VertexQueue *vq;
    Vertex *v;
    Edge *e;
    vq = NewVertexQueue();
    v = g->vertices[start-1];
    v->discovered = 1;
    EnqueueVertex(vq, v);
    
    while (VertexQueueIsEmpty(vq) == 0) {
        
        v = DequeueVertex(vq);
        ProcessVertexEarly(g,v);
        v->processed = 1;
        e = g->edges[VertIndex(v)];
        
        while (e != NULL) {
            
            int si = e->y - 1;
            Vertex *s = g->vertices[si];
            
            if (s->processed == 0){
                ProcessEdge(g,e,v);
            }
            
            if (s->discovered == 0){
                EnqueueVertex(vq, s);
                s->discovered = 1;
                s->parent = v->x;
            }
            
            if (e->next){
                e = e->next;
            }else{
                break;
            }
        }
        
        ProcessVertexLate(g,v);
    }
}

int DijkstraShortestPathWithDice(Graph *g, int start, int end){
    
    int i;
    Edge *e;
    int inTree[MAXV+1];
    int rolls[MAXV+1];
    int dice[MAXV+1];
    Vertex *v;
    Vertex *c;
    int weight;
    int mrolls = -1;
    int mdice = -1;
    for (i = 1; i <= g->nvertices; i ++){
        inTree[i] = 0;
        rolls[i] = MAXINT;
        dice[i] = 0;
        (g->vertices[i-1])->discovered = 0;
        (g->vertices[i-1])->processed = 0;
        (g->vertices[i-1])->parent = 0;
    }
    
    rolls[start] = 1;
    dice[start] = 0;
    
    v = g->vertices[start-1];
    
    while (inTree[v->x] == 0) {
        inTree[v->x] = 1;
        
        e = g->edges[VertIndex(v)];
        
        while (e) {
            
            c = g->vertices[e->y - 1];
            weight = e->w;
            
            int diceVal = dice[v->x];
            int newVal = diceVal+weight;
            int addRoll = (newVal>=NSIDES) ? 1 : 0;
            
            if (newVal <= NSIDES && rolls[c->x] > rolls[v->x] + addRoll){
                
                newVal = ( addRoll || ResetDice(e)) ? 0 : newVal;
                dice[c->x] = newVal;
                rolls[c->x] = rolls[v->x] + addRoll;
                c->parent = v->x;
                
            }
            
            e = e->next;
        }
        
        v = g->vertices[0];
        mrolls = MAXINT;
        
        for (i = 1; i <= g->nvertices; i++){
            
            if ((inTree[i] == 0) && mrolls > rolls[i] && mdice > dice[i]){
                mrolls = rolls[i];
                v = g->vertices[i-1];
            }
            
        }
    }
    
    int path[MAXV+1];
    memset(path, 0, sizeof(int)*(MAXV+1));
    v = g->vertices[end-1];
    int len = GetPath(g, v, path);
    
    int retval = rolls[end];
#ifdef XCODE_TEST_DEBUG
    printf("Path:\n");
    for (i = 0; i< len; i++){
        printf("%d) %d (rolls = %d, dice val = %d)\n",i+1,path[i],rolls[path[i]],dice[path[i]]);
    }
    printf("\n");
#endif
    
    if (retval == MAXINT) retval = ERR;
    
    return retval;
}


int DijkstraShortestPath(Graph *g, int start, int end){
    
    int i;
    Edge *e;
    int inTree[MAXV+1];
    int distance[MAXV+1];
    Vertex *v;
    Vertex *c;
    int weight;
    int dist = -1;
    
    for (i = 1; i <= g->nvertices; i ++){
        inTree[i] = 0;
        distance[i] = MAXINT;
        (g->vertices[i-1])->discovered = 0;
        (g->vertices[i-1])->processed = 0;
        (g->vertices[i-1])->parent = 0;
    }
    
    distance[start] = 0;
    
    v = g->vertices[start-1];
    
    while (inTree[v->x] == 0) {
        inTree[v->x] = 1;
        
        e = g->edges[VertIndex(v)];
        
        while (e) {
            
            c = g->vertices[e->y - 1];
            weight = e->w;
            
            if (distance[c->x] > (distance[v->x] + weight)){
                distance[c->x] = distance[v->x]+ weight;
                c->parent = v->x;
            }
        
            e = e->next;
        }
        
        v = g->vertices[0];
        dist = MAXINT;
        
        for (i = 1; i <= g->nvertices; i++){

            if ((inTree[i] == 0) && dist > distance[i]){
                dist = distance[i];
                v = g->vertices[i-1];
            }
        }
    }
    
    return distance[end];
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
        
        int ladders[MAXV+2];
        memset(ladders, 0, sizeof(int)*(MAXV+2));
        
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

            ladders[start] = end;
            
        }
        
        
        
        int M;
#ifndef XCODE_TEST_RUN
        scanf("%d",&M);
#else
        sscanf(input+in_bytes_consumed, "%d%n",&M,&in_bytes_now);
        in_bytes_consumed+=in_bytes_now;
#endif
        int snakes[MAXV+2];
        memset(snakes, 0, sizeof(int)*(MAXV+2));
        
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
            snakes[start] = end;
            
        }
        
        
        Graph *g = NewGraph(1);
        InsertSnakesAndLadders(g, ladders, snakes);
#ifdef XCODE_TEST_DEBUG
        //PrintGraph(g);
#endif
        
        
        int rolls = DijkstraShortestPathWithDice(g,1,100);
        
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
