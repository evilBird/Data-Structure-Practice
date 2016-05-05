//
//  MedianUpdates.c
//  Data Structure Practice
//
//  Created by Travis Henspeter on 4/29/16.
//  Copyright © 2016 birdSound. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
/* Head ends here */

int Compare(int a, int b){
    return (a-b);
}

typedef struct Node_{
    int val;
    int ht;
    struct Node_ *left;
    struct Node_ *right;
}Node;

void NodeInit(Node *n){
    n->val = 0;
    n->ht = 0;
    n->left = NULL;
    n->right = NULL;
}

int GetNodeHt(Node *n){
    
    if (n->left == NULL && n->right == NULL){
        return 0;
    }
    
    if (n->left == NULL && n->right != NULL){
        int ht = GetNodeHt(n->right);
        return (ht + 1);
    }
    
    if (n->left != NULL && n->right == NULL){
        int ht = GetNodeHt(n->left);
        return (ht + 1);
    }
    
    int ht = (GetNodeHt(n->left) > GetNodeHt(n->right)) ? (GetNodeHt(n->left)) : (GetNodeHt(n->right));
    return ht;
}

int GetNodeFactor(Node *n){
    
    if (n == NULL){
        return 0;
    }
    
    if (n->left == NULL && n->right == NULL){
        return 0;
    }
    
    if (n->left == NULL && n->right != NULL){
        return GetNodeHt(n->right) + 1;
    }
    
    if (n->left != NULL && n->right == NULL){
        return GetNodeHt(n->left) - 1;
    }
    
    int factor = GetNodeHt(n->right)-GetNodeHt(n->left);
    return factor;
}

void NodeCreate(Node **n){
    *n = (Node *)malloc(sizeof(Node));
    NodeInit(*n);
}

typedef struct Tree_{
    int size;
    Node *root;
}Tree;

void TreeInit(Tree *t){
    t->size = 0;
    t->root = NULL;
}

Tree * TreeCreate() {
    Tree *t = (Tree *)malloc(sizeof(Tree));
    TreeInit(t);
    return t;
}

void PrintNode(Node *n){
    if (n->left){
        PrintNode(n->left);
    }
    //printf("[%d (%d)] ",n->val,GetNodeFactor(n));
    printf("%d ",n->val);
    if (n->right) {
        PrintNode(n->right);
    }
}

int TreeHeight(Tree *t, Node *n){
    
    if (!n ) {
        if ( t->root ) return TreeHeight(t, t->root);
        else return 0;
    }
    
    int leftHt = 0;
    
    if (n->left){
        leftHt = TreeHeight(t, n->left);
    }
    
    int rightHt = 0;
    
    if (n->right){
        rightHt = TreeHeight(t, n->right);
    }
    
    int ht = (leftHt > rightHt) ? rightHt : leftHt;
    return ht + 1;
}

void PrintTree(Tree *t){
    printf("\ntree n = %d h = %d\n",t->size,TreeHeight(t, NULL));
    if (t->root){
        PrintNode(t->root);
    }
    printf("\n\n");
}

void DoRR(Node **n){
    printf("RR on %d (f = %d)\n",(*n)->val,GetNodeFactor(*n));
    Node *newLeft = *n;
    Node *newRoot = (*n)->right;
    newLeft->right = newRoot->left;
    newRoot->left = newLeft;
    *n = newRoot;
}

void DoRL(Node **n){
    printf("RL on %d\n",(*n)->val);
    Node **right = &((*n)->right);
    Node *newRight = (*right)->left;
    (*right)->left = newRight->right;
    newRight->right = (*right);
    *right = newRight;
}

void BalanceR(Node **n){
    
    if (GetNodeFactor((*n)->left) == -1){
        DoRL(n);
    }
    
    DoRR(n);
}

void DoLL(Node **n){
    printf("LL on %d\n",(*n)->val);
    Node *newRight = *n;
    Node *newRoot = newRight->left;
    newRight->left = newRoot->right;
    newRoot->right = newRight;
    
    *n = newRoot;
}

void DoLR(Node **n){
    printf("LR on %d\n",(*n)->val);
    Node **left = &((*n)->left);
    Node *newLeft = (*left)->right;
    (*left)->right = newLeft->left;
    newLeft->left = (*left);
    *left = newLeft;
}

void BalanceL(Node **n){
    if (GetNodeFactor((*n)->left) == 1){
        DoLR(n);
    }
    
    DoLL(n);
}

Node * TreeInsert(Tree *t, Node **n, int val){
    
    if ( *n == NULL ){
        NodeCreate(n);
        (*n)->val = val;
        t->size ++;
        //printf("inserted %d tree size %d\n",val,t->size);
        return (*n);
    }
    
    Node *retval;
    int cmp = Compare(val, (*n)->val);
    
    if (cmp < 0){
        //printf("insert left of %d\n",(*n)->val);
        retval = TreeInsert(t,&((*n)->left),val);
    }else if (cmp > 0){
        //printf("insert right of %d\n",(*n)->val);
        retval = TreeInsert(t,&((*n)->right),val);
    }
    
    int factor = GetNodeFactor(*n);
    //printf("node %d factor = %d\n",(*n)->val,factor);
    
    if (factor == -2){
        
        BalanceL(n);
        //printf("post balance L node %d factor = %d\n",(*n)->val,GetNodeFactor(*n));
    }else if (factor == 2){
        BalanceR(n);
        //printf("post balance R node %d factor = %d\n",(*n)->val,GetNodeFactor(*n));
    }
    
    return retval;
}

int TreeRemove(Tree *t, Node **node, int val){
    return 0;
}


void median(int N,char *s, int *x, Tree *t) {
    int v = *x;
    TreeInsert(t,&t->root,v);
}

int GetValueAtIndex(Node *n, int idx, int i, int *val){
    int myIndex;
    
    if (n->left){
        myIndex = 1 + GetValueAtIndex(n->left,idx,i,val);
    }else{
        myIndex = i;
    }

    
    if (myIndex == idx){
        *val = n->val;
        return myIndex;
    }
    
    if (n->right){
        GetValueAtIndex(n->right,idx,(myIndex + 1),val);
    }
    
    return myIndex;
}

float TreeGetMedian(Tree *t){
    
    int size = t->size;
    if (size <=0 ) return 0;
    int idx = size/2;
    printf("median idx = %d\n",idx);
    int v;
    GetValueAtIndex(t->root, idx, 0, &v);
    float val = (float)v;
    printf("value at idx %d = %.1f\n",idx,val);
    if (size%2 == 0){
        idx--;
        int v2;
        GetValueAtIndex(t->root, idx, 0,&v);
        float val1 = (float)v2;
        printf("value at idx %d = %.1f\n",idx,val1);
        val+= val1;
        val*=0.5;
    }
    
    return val;
}

int RunDefaultCase()
{
    int N = 100;
    //char *S[7] = {"a","a","a","a","a","a","a"};
    //int X[7] = {4, 2, 7, 1, 6, 5, 3};
    
    int V[11] = {14, 25, 21, 10, 23, 7, 26, 12, 30, 16, 19};
    Tree *t = TreeCreate();
    
    for (int i = 0; i < N; i ++){
        //median(N, S[i], &X[i], t);
        //PrintTree(t);
        TreeInsert(t,&t->root,i);
        //PrintTree(t);
        //float f = (int)floorf(logf((float)(t->size)));
        //printf("For n = %d E(h) = %f\n",(t->size),f);
        PrintTree(t);
        //float median = TreeGetMedian(t);
        //printf("median: %.1f\n",median);
    }
    
    return 0;
}
