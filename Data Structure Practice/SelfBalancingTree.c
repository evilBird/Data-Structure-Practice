//
//  SelfBalancingTree.c
//  Data Structure Practice
//
//  Created by Travis Henspeter on 5/10/16.
//  Copyright © 2016 birdSound. All rights reserved.
//

#include "SelfBalancingTree.h"
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

#define XCODE_TEST_RUN

 typedef struct node
 {
 int val;
 struct node* left;
 struct node* right;
 int ht;
 } node;

int Compare(int a, int b){
    return (a-b);
}

void NodeInit(node *n){
    n->val = 0;
    n->ht = 0;
    n->left = NULL;
    n->right = NULL;
}

node * NewNode(){
    node *n = (node *)malloc(sizeof(node));
    NodeInit(n);
    return n;
}

int UpdateHt(node *n){
    
    if (!n) return -1;
    
    int leftHt = -1;
    int rightHt = -1;
    int myHt;
    
    if (n->left){
        leftHt = UpdateHt(n->left);
    }
    
    if (n->right){
        rightHt = UpdateHt(n->right);
    }
    
    if (leftHt < 0 && rightHt < 0){
        myHt = 0;
        n->ht = myHt;
        return myHt;
    }else{
        myHt = ( leftHt > rightHt ) ? leftHt : rightHt;
    }
    
    n->ht = (myHt + 1);
    return (n->ht);
}

int GetNodeFactor(node *n){
    
    if (n == NULL){
        return 0;
    }
    int factor = UpdateHt(n->left)-UpdateHt(n->right);
    return factor;
}

void PrintNodeIO(node *n){
    
    if (n->left){
        PrintNodeIO(n->left);
    }
    
    printf("%d(HT=%d, BF=%d) ",n->val, n->ht,GetNodeFactor(n));
    
    if (n->right) {
        PrintNodeIO(n->right);
    }
}

void PrintNodePO(node *n){
    
    printf("%d(HT=%d, BF=%d) ",n->val, n->ht,GetNodeFactor(n));
    
    if (n->left){
        PrintNodePO(n->left);
    }
    
    if (n->right) {
        PrintNodePO(n->right);
    }
}

void PrintTree(node *root){
    
    PrintNodeIO(root);
    PrintNodePO(root);
    printf("\n");
}

int PrintNodeResultIO(node *n, char *buf){
    
    int out_bytes_now = 0;
    int bytes_consumed = 0;
    
    if (n->left){
        out_bytes_now = PrintNodeResultIO(n->left, buf);
        bytes_consumed+=out_bytes_now;
        buf+=out_bytes_now;
        out_bytes_now = sprintf(buf," ");
        bytes_consumed+=out_bytes_now;
        buf+=out_bytes_now;
    }
    
    out_bytes_now = sprintf(buf,"%d(BF=%d)",n->val,GetNodeFactor(n));
    bytes_consumed+=out_bytes_now;
    buf+=out_bytes_now;
    
    if (n->right) {
        out_bytes_now = sprintf(buf," ");
        bytes_consumed+=out_bytes_now;
        buf+=out_bytes_now;
        out_bytes_now = PrintNodeResultIO(n->right,buf);
        bytes_consumed+=out_bytes_now;
        buf+=out_bytes_now;
    }
    
    return bytes_consumed;
}

int PrintNodeResultPO(node *n, char *buf){
    
    int out_bytes_now = 0;
    int bytes_consumed = 0;
    out_bytes_now = sprintf(buf,"%d(BF=%d)",n->val,GetNodeFactor(n));
    bytes_consumed+=out_bytes_now;
    buf+=out_bytes_now;
    
    
    if (n->left){
        out_bytes_now = sprintf(buf," ");
        bytes_consumed+=out_bytes_now;
        buf+=out_bytes_now;
        out_bytes_now = PrintNodeResultPO(n->left,buf);
        bytes_consumed+=out_bytes_now;
        buf += out_bytes_now;
    }
    
    if (n->right) {
        out_bytes_now = sprintf(buf," ");
        bytes_consumed+=out_bytes_now;
        buf+=out_bytes_now;
        out_bytes_now = PrintNodeResultPO(n->right,buf);
        bytes_consumed+=out_bytes_now;
        buf += out_bytes_now;
    }
    
    return bytes_consumed;
}

int PrintResult(node *root, char *buf){
    int out_bytes_now = 0;
    int bytes_consumed = 0;
    
    out_bytes_now = PrintNodeResultIO(root,buf);
    bytes_consumed+=out_bytes_now;
    buf+=out_bytes_now;
    out_bytes_now = sprintf(buf,"\n");
    bytes_consumed+=out_bytes_now;
    buf+=out_bytes_now;
    
    out_bytes_now = PrintNodeResultPO(root,buf);
    bytes_consumed+=out_bytes_now;
    buf+=out_bytes_now;
    //out_bytes_now = sprintf(buf,"\n");
    //bytes_consumed+=out_bytes_now;
    //buf+=out_bytes_now;
    
    return bytes_consumed;
}

void DoRR(node **n){
    
    printf("RR on %d\n",(*n)->val);
    node *newLeft = *n;
    node *newRoot = (*n)->right;
    newLeft->right = newRoot->left;
    newRoot->left = newLeft;
    *n = newRoot;
}

void DoRL(node **n){
    
    printf("RL on %d\n",(*n)->val);
    node **right = &((*n)->right);
    node *newRight = (*right)->left;
    (*right)->left = newRight->right;
    newRight->right = (*right);
    *right = newRight;
}

void BalanceR(node **n){
    
    if (GetNodeFactor((*n)->right) == 1){
        DoRL(n);
    }
    
    DoRR(n);
}

void DoLL(node **n){
    
    printf("LL on %d\n",(*n)->val);
    node *newRight = *n;
    node *newRoot = newRight->left;
    newRight->left = newRoot->right;
    newRoot->right = newRight;
    
    *n = newRoot;
}

void DoLR(node **n){
    
    printf("LR on %d\n",(*n)->val);
    node **left = &((*n)->left);
    node *newLeft = (*left)->right;
    (*left)->right = newLeft->left;
    newLeft->left = (*left);
    *left = newLeft;
}

void BalanceL(node **n){
    
    if (GetNodeFactor((*n)->left) == -1){
        DoLR(n);
    }
    
    DoLL(n);
}

node * InsertNode(node *r, node **n, int val, int *flag){
    
    if ( *n == NULL ){
        *n = NewNode();
        (*n)->val = val;
        (*n)->ht = 0;
        *flag = 1;
        return (*n);
    }
    
    node *retval = NULL;
    
    int cmp = Compare(val, (*n)->val);
    
    if (cmp < 0){
        
        retval = InsertNode(*n,&((*n)->left),val,flag);
        
    }else if (cmp > 0){
        
        retval = InsertNode(*n,&((*n)->right),val,flag);
    }
    
    if ( *flag ){
        *flag = 0;
        return retval;
    }
    
    UpdateHt(*n);
    int factor = GetNodeFactor(*n);
    if (abs(factor)==2){
        //printf("node %d needs to be balanced (factor = %d)\n",(*n)->val,factor);
        if (factor == -2){
            BalanceR(n);
        }else if (factor == 2){
            BalanceL(n);
        }
        
    }
    return retval;
}

#ifdef XCODE_TEST_RUN
int SelfBalancingTreeRunTestCase(char *output, const char *input){

    int N;
    int in_bytes_consumed = 0, in_bytes_now = 0;
    sscanf(input, "%d%n",&N,&in_bytes_now);
    in_bytes_consumed+=in_bytes_now;
    
    node *root = NULL;
    
    for (int n = 0; n < N; n ++){
        int f = 0;
        int val;
        sscanf(input+in_bytes_consumed,"%d%n",&val,&in_bytes_now);
        in_bytes_consumed+=in_bytes_now;
        InsertNode(root, &root,val, &f);
    }
    
    int val;
    sscanf(input+in_bytes_consumed,"%d%n",&val,&in_bytes_now);
    in_bytes_consumed+=in_bytes_now;
    
#else
    
node * insert(node * root,int val){
    
#endif
    
    int flag = 0;
    InsertNode(root,&root,val,&flag);
#ifdef XCODE_TEST_DEBUG
    PrintTree(root);
#endif
#ifdef XCODE_TEST_RUN
    PrintResult(root,output);
    return 0;
    
#else
    
    return root;
#endif
    
    
}