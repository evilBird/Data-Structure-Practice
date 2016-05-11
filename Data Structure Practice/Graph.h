//
//  Graph.h
//  Data Structure Practice
//
//  Created by Travis Henspeter on 5/10/16.
//  Copyright © 2016 birdSound. All rights reserved.
//

#ifndef Graph_h
#define Graph_h

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define MAXV 100
#define MAXINT 100000000
#define ERR -1

#define VertIndex(v)        (((v)->x) - 1)
#define EdgeIndex(e)        (((e)->x) - 1)

typedef enum EdgeCls_{
    EdgeCls_Tree    = 0,
    EdgeCls_Back    = 1,
    EdgeCls_Forward = 2,
    EdgeCls_Cross   = 3
}EdgeCls;

typedef struct Edge_{
    int         x;
    int         y;
    int         w;
    EdgeCls     cls;
    struct  Edge_ *next;
}Edge;

Edge * CreateNewEdge(int x, int y, int w);

void PrintEdge(Edge *e);


typedef struct Vertex_{
    int     x;
    int     discovered;
    int     processed;
    int     parent;
    
    int     t_entry;
    int     t_exit;
    
    int     reachable_ancestor;
    int     tree_out_degree;
    
}Vertex;

Vertex * NewVertex();

void PrintVertex(Vertex *v);

typedef struct VertexQueue_{
    
    int     n;
    Vertex  *vertices[MAXV+1];
    
}VertexQueue;

int VertexQueueIsEmpty(VertexQueue *vq);

void EnqueueVertex(VertexQueue *vq, Vertex *v);

Vertex *DequeueVertex(VertexQueue *vq);

VertexQueue * NewVertexQueue();

#define VertexStack         VertexQueue
#define NewVertexStack      NewVertexQueue
#define VertexStackIsEmpty  VertexQueueIsEmpty

void PushVertex(VertexStack *vs, Vertex *v);
Vertex * PopVertex(VertexStack *vs);

typedef struct Graph_{
    
    int     nvertices;
    int     nedges;
    int     directed;
    
    int     degrees[MAXV+1];
    
    Vertex  *vertices[MAXV+1];
    Edge    *edges[MAXV+1];
    
    int     time;
    int     finished;
    
    int     (*proc_vert_e)  (struct Graph_ *, Vertex *);
    int     (*proc_edge)    (struct Graph_ *, Edge *);
    int     (*proc_vert_l)  (struct Graph_ *, Vertex *);
    
    VertexQueue *vq;
    VertexStack *vs;
    
}Graph;

Graph * NewGraph(int directed);

void InsertEdge(Graph *g, Edge *e, int directed);

EdgeCls ClassifyEdge(Graph *g, Edge *e);

void PrintGraph(Graph *g);

void InitializeSearch(Graph *g);

void GraphBFS(Graph *g, int start);

void GraphDFS(Graph *g, int start);

int GraphTopoSort(Graph *g);

int Prim(Graph *g, int start);

int DijkstraShortestPath(Graph *g, int start, int end);



#endif /* Graph_h */
