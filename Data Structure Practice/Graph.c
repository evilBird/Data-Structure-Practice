//
//  Graph.c
//  Data Structure Practice
//
//  Created by Travis Henspeter on 5/10/16.
//  Copyright © 2016 birdSound. All rights reserved.
//

#include "Graph.h"
#define XCODE_TEST_DEBUG
#define ALLOCATE(name)      ((name*)(malloc(sizeof(name))))

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

Edge * EdgeComplement(Edge *e){
    Edge *ec = NewEdge();
    ec->x = e->y;
    ec->y = e->x;
    return ec;
}

void PrintEdge(Edge *e){
    printf("\tEdge %d - %d (w = %d)\n",e->x,e->y,e->w);
}

void InitializeVertex(Vertex *v){
    v->x = 0;
    v->discovered = 0;
    v->processed = 0;
    v->parent = 0;
    v->t_entry = 0;
    v->t_exit = 0;
    v->reachable_ancestor = 0;
    v->tree_out_degree = 0;
}

Vertex * NewVertex(){
    Vertex *v = ALLOCATE(Vertex);
    InitializeVertex(v);
    return v;
}

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

void InitializeGraph(Graph *g){
    
    g->nvertices = 0;
    g->nedges = 0;
    g->directed = 0;
    g->proc_vert_e = NULL;
    g->proc_edge = NULL;
    g->proc_vert_l = NULL;
    g->vq = NULL;
    g->vs = NULL;
    
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

void InsertEdge(Graph *g, Edge *e, int directed){
    
    Edge **pos;
    
    if (g->degrees[EdgeIndex(e)] == 0){
        pos = &g->edges[EdgeIndex(e)];
    }else{
        Edge *ne = g->edges[EdgeIndex(e)];
        while (ne->next) {
            ne = ne->next;
        }
        pos = &ne->next;
    }
    
    *pos = e;
    g->degrees[EdgeIndex(e)]++;
    
    if (directed == 0){
        Edge *ec = EdgeComplement(e);
        InsertEdge(g, ec, 1);
    }else{
        g->nedges++;
    }
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
void InitializeSearch(Graph *g){
    g->time = 0;
    g->finished = 0;
    for (int i = 0; i < g->nvertices; i++) {
        (g->vertices[i])->t_entry = 0;
        (g->vertices[i])->t_exit = 0;
        (g->vertices[i])->discovered = 0;
        (g->vertices[i])->processed = 0;
        (g->vertices[i])->parent = 0;
        (g->vertices[i])->reachable_ancestor = 0;
        (g->vertices[i])->tree_out_degree = 0;
    }
}

int ProcessVertexEarly(Graph *g, Vertex *v){
    
    if (g->proc_vert_e){
        return g->proc_vert_e(g,v);
    }
    
#ifdef XCODE_TEST_DEBUG
    printf("Early Process Vertex %d\n",v->x);
    PrintVertex(v);
#endif
    return 0;
}

int ProcessVertexLate(Graph *g, Vertex *v){
    
    if (g->proc_vert_l){
        return g->proc_vert_l(g,v);
    }
    
#ifdef XCODE_TEST_DEBUG
    printf("Late Process Vertex %d\n",v->x);
    PrintVertex(v);
#endif
    return 0;
}

int ProcessEdge(Graph *g, Edge *e){
    
    if (g->proc_edge){
        return g->proc_edge(g,e);
    }
    
#ifdef XCODE_TEST_DEBUG
    PrintEdge(e);
#endif
    return 0;
}


EdgeCls ClassifyEdge(Graph *g, Edge *e){
    
    Vertex *x = g->vertices[e->x - 1];
    Vertex *y = g->vertices[e->y - 1];
    
    if (y->parent == x->x) return EdgeCls_Tree;
    if (y->discovered && !(y->processed)) return EdgeCls_Back;
    if (y->processed && (y->t_entry > x->t_entry)) return EdgeCls_Forward;
    if (y->processed && (y->t_entry < x->t_entry)) return EdgeCls_Cross;
    
    return 0;
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
            
            if (s->processed == 0 || g->directed){
                
                ProcessEdge(g, e);
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
        
        ProcessVertexLate(g, v);
    }
    
}

int GraphDFS_ProcessVertexEarly(Graph *g, Vertex *v){
    v->reachable_ancestor = v->x;
    return 0;
}

int GraphDFS_ProcessEdge(Graph *g, Edge *e){
    
    Vertex *x = g->vertices[e->x - 1];
    Vertex *y = g->vertices[e->y - 1];
    
    e->cls = ClassifyEdge(g, e);
    
    if (e->cls == EdgeCls_Tree){
        
        x->tree_out_degree++;
        
    }else if (e->cls == EdgeCls_Back && x->parent != y->x){
        
        Vertex *ra = g->vertices[x->reachable_ancestor - 1];
        if (y->t_entry < ra->t_entry){
            x->reachable_ancestor = y->x;
        }
    }
    return (x->reachable_ancestor);
}

int GraphDFS_ProcessVertexLate(Graph *g, Vertex *v){
    
    int root;
    int time_v;
    int time_parent;
    if (v->parent < 1){
        if (v->tree_out_degree > 1){
            printf("root articulation vertex: %d\n",v->x);
            return 0;
        }
    }
    Vertex *p = g->vertices[v->parent - 1];
    root = (p->parent < 1);
    if (v->reachable_ancestor == v->parent && !root){
        printf("parent articulation vertex: %d\n",v->parent);
    }
    if (v->reachable_ancestor == v->x){
        printf("bridge articulation vertex: %d\n",v->parent);
        if (v->tree_out_degree > 0){
            printf("bridge articulation vertex: %d\n",v->x);
        }
    }
    Vertex *ra = g->vertices[v->reachable_ancestor - 1];
    time_v = ra->t_entry;
    Vertex *rap = g->vertices[ra->parent - 1];
    time_parent = rap->t_entry;
    if (time_v < time_parent){
        p->reachable_ancestor = v->reachable_ancestor;
    }
    
    return 0;
}

void GraphDFS(Graph *g, int start){
    
    Vertex *v,*s;
    Edge *e;
    if (g->finished) return;
    int idx = start-1;
    v = g->vertices[idx];
    v->discovered = 1;
    g->time++;
    v->t_entry = g->time;
    

    ProcessVertexEarly(g,v);
    
    e = g->edges[VertIndex(v)];
    
    while (e) {
        
        int sidx = e->y-1;
        s = g->vertices[sidx];
        
        if (s->discovered == 0){
            
            s->parent = v->x;

            ProcessEdge(g,e);
            
            GraphDFS(g,e->y);
            
        }else if (s->processed == 0 || g->directed){
            
            ProcessEdge(g,e);
        }
        
        if (g->finished) return;
        
        e = e->next;
    }
    
    ProcessVertexLate(g, v);
    g->time++;
    v->t_exit = g->time;
    v->processed = 1;
}

int GraphTopoSort_ProcessVertexEarly(Graph *g, Vertex *v){
    return 0;
}

int GraphTopoSort_ProcessEdge(Graph *g, Edge *e){
    EdgeCls cls = ClassifyEdge(g, e);
    if (cls == EdgeCls_Back){
        printf("WARNING: Directed cycle found...\n");
        return -1;
    }
    
    return 0;
}

int GraphTopoSort_ProcessVertexLate(Graph *g, Vertex *v){
    PushVertex(g->vs, v);
    return 0;
}

int GraphTopoSort(Graph *g){
    
    int i;
    VertexStack **mvs = &g->vs;
    VertexStack *s = NewVertexStack();
    *mvs = s;
    InitializeSearch(g);
    g->proc_vert_e = GraphTopoSort_ProcessVertexEarly;
    g->proc_edge = GraphTopoSort_ProcessEdge;
    g->proc_vert_l = GraphTopoSort_ProcessVertexLate;
    
    for (i = 1; i<=g->nvertices; i++){
        Vertex *v = g->vertices[i-1];
        if (v->discovered == 0){
            GraphDFS(g, v->x);
        }
    }
    
    while (VertexStackIsEmpty(g->vs) == 0) {
        Vertex *v = PopVertex(g->vs);
        PrintVertex(v);
    }
    
    return 0;
}

int Prim(Graph *g, int start){
    
    int i;
    Edge *e;
    int inTree[MAXV+1];
    int distance[MAXV+1];
    Vertex *v;
    Vertex *c;
    int weight;
    int dist = -1;
    
    for (int i = 1; i <=g->nvertices; i++){
        inTree[i] = 0;
        distance[i] = 0;
        (g->vertices[i-1])->parent = -1;
    }
    
    distance[start] = 0;
    v = g->vertices[start-1];
    
    while (inTree[v->x] == 0) {
        
        inTree[v->x] = 1;
        e = g->edges[VertIndex(v)];
        
        while (e) {
            
            c = g->vertices[e->y - 1];
            weight = e->w;
            if ((distance[c->x] > weight) && inTree[c->x] == 0){
                distance[c->x] = weight;
                c->parent = v->x;
            }
            e = e->next;
        }
        
        v = g->vertices[0];
        dist = MAXINT;
        for (i = 1; i <= g->nvertices; i++){
            if ((inTree[i] == 0) && (dist > distance[i])){
                dist = distance[i];
                v = g->vertices[i-1];
            }
        }
    }
    
    return dist;
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
