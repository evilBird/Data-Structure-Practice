//
//  SnakesAndLadders.c
//  Data Structure Practice
//
//  Created by Travis Henspeter on 5/4/16.
//  Copyright © 2016 birdSound. All rights reserved.
//

#include "SnakesAndLadders.h"
#include "Graph.h"

#define NSIDES 6
#define EdgeIsLadder(e)     ((((e)->y - (e)->x) > 1 ) ? 1 : 0)
#define EdgeIsSnake(e)      ((((e)->x - (e)->y) > 1 ) ? 1 : 0)
#define ResetDice(e)        ((( EdgeIsLadder(e) || EdgeIsSnake (e) ) == 1) ? 1 : 0)


void InsertSnakesAndLadders(Graph *g, int *ladders, int *snakes){
    
    int lastEmpty = 1;
    
    for (int x = 1; x < g->nvertices; x ++){
        
        if (ladders[x]){
            
            int y = ladders[x];
            Edge *ladder = CreateNewEdge(x, y, 0);
            InsertEdge(g, ladder, 1);
            Edge *e = CreateNewEdge(lastEmpty, x, x-lastEmpty);
            InsertEdge(g, e, 1);
            
        }else if (snakes[x]){
            
            int y = snakes[x];
            Edge *snake = CreateNewEdge(x, y, 0);
            InsertEdge(g, snake, 1);
            Edge *e = CreateNewEdge(lastEmpty, x, x-lastEmpty);
            InsertEdge(g, e, 1);
            
        }else{
            
            if (x > lastEmpty){
                Edge *e = CreateNewEdge(lastEmpty, x, x-lastEmpty);
                InsertEdge(g, e, 1);
            }
            
            lastEmpty = x;
        }
    }
    
    Edge *e = CreateNewEdge(lastEmpty, g->nvertices, g->nvertices-lastEmpty);
    InsertEdge(g, e, 1);
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
