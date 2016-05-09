//
//  GraphPractice.c
//  Data Structure Practice
//
//  Created by Travis Henspeter on 5/9/16.
//  Copyright © 2016 birdSound. All rights reserved.
//

#include "GraphPractice.h"
#include <stdlib.h>
#include <string.h>
#include <math.h>


#define MAXV 100
#define ERR -1

#define ALLOCATE(name)      ((name*)(malloc(sizeof(name))))
#define VertIndex(v)        (((v)->x) - 1)
#define EdgeIndex(e)        (((e)->x) - 1)

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
            printf("\tDegree %d\n",g->degrees[i]);
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

void ProcessVertexEarly(Graph *g, Vertex *v){
    //printf("Early Process Vertex %d\n",v->x);
    //PrintVertex(v);
}

void ProcessVertexLate(Graph *g, Vertex *v){
    printf("Late Process Vertex %d\n",v->x);
    PrintVertex(v);
    if (v->x == 100){
        PrintPath(g, v);
    }
}

void ProcessEdge(Graph *g, Edge *e, Vertex *v){
    PrintEdge(e);
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

void TestGraphPractice(){
    Graph *g = NewGraph(1);
    int ladders[MAXV+2];
    memset(ladders, 0, sizeof(int)*MAXV+2);
    ladders[5] = 50;
    ladders[12] = 72;
    ladders[34] = 56;
    int snakes[MAXV+2];
    memset(snakes, 0, sizeof(int)*MAXV+2);
    snakes[46] = 4;
    snakes[67] = 21;
    snakes[90] = 10;
    InsertSnakesAndLadders(g, ladders, snakes);
    PrintGraph(g);
    InitializeSearch(g);
    GraphBFS(g, 1);
}
