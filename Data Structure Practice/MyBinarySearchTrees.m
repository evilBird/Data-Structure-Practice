//
//  MyBinarySearchTrees.m
//  Data Structure Practice
//
//  Created by Travis Henspeter on 4/6/16.
//  Copyright © 2016 birdSound. All rights reserved.
//

#import "MyBinarySearchTrees.h"

@implementation MyBinarySearchTrees

int BinarySearchTreeNode_CompareFloats(const void *key1, const void *key2){
    return (*(float*)key1)-(*(float*)key2);
}

void BinarySearchTreeNode_Print(BinarySearchTreeNode *node, const void *data){
    printf("node data = %f, balance = %d, hidden = %d\n",(*(float *)BinarySearchTreeNode_Data(node)),node->factor,node->hidden);
}

BinarySearchTreeNode* BinarySearchTreeNodeCreate(){
    BinarySearchTreeNode *node = (BinarySearchTreeNode *)(malloc(sizeof(BinarySearchTreeNode)));
    node->factor = 0;
    node->hidden = 0;
    node->left = NULL;
    node->right = NULL;
    node->data = NULL;
    return node;
}

void BinarySearchTreeNodeDestroyLeft(BinarySearchTreeNode *node){
    
    node->left->data = NULL;
    free(node->left);
    node->left = NULL;
}

void BinarySearchTreeNodeDestroyRight(BinarySearchTreeNode *node){
    node->right->data = NULL;
    free(node->right);
    node->right = NULL;
}

void BinarySearchTreeNodeDestroy(BinarySearchTreeNode *node){
    
    if (node == NULL) {
        return;
    }
    
    if (BinarySearchTreeNode_Left(node)){
        
        if (BinarySearchTreeNode_isLeaf(BinarySearchTreeNode_Left(node))) {
            BinarySearchTreeNodeDestroyLeft(node);
        }else{
            BinarySearchTreeNodeDestroy(BinarySearchTreeNode_Left(node));
        }
    }
    
    if (BinarySearchTreeNode_Right(node)){
        if (BinarySearchTreeNode_isLeaf(BinarySearchTreeNode_Right(node))) {
            BinarySearchTreeNodeDestroyRight(node);
        }else{
            BinarySearchTreeNodeDestroy(BinarySearchTreeNode_Right(node));
        }
    }
}

void BinarySearchTreeNodeRotateLeft(BinarySearchTreeNode **node)
{
    BinarySearchTreeNode *left, *grandchild;
    left = BinarySearchTreeNode_Left(*node);
    
    if ((left)->factor == -1) {
        //LL Rotation
        BinarySearchTreeNode_Left(*node) = BinarySearchTreeNode_Right(left);
        BinarySearchTreeNode_Right(left) = *node;
        (*node)->factor = 0;
        (left)->factor = 0;
        *node = left;
    }else{
        //LR Rotation
        grandchild = BinarySearchTreeNode_Right(left);
        BinarySearchTreeNode_Right(left) = BinarySearchTreeNode_Left(grandchild);
        BinarySearchTreeNode_Left(grandchild) = left;
        BinarySearchTreeNode_Left(*node) = BinarySearchTreeNode_Right(grandchild);
        BinarySearchTreeNode_Right(grandchild) = *node;
        
        switch((grandchild)->factor){
            case -1:{
                (*node)->factor = 1;
                (left)->factor = 0;
            }
                break;
            case 0:{
                (*node)->factor = 0;
                (left)->factor = 0;
            }
                break;
            case 1:{
                (*node)->factor = 0;
                (left)->factor = -1;
            }
                break;
        }
        
        (grandchild)->factor = 0;
        *node = grandchild;
    }
    
}

void BinarySearchTreeNodeRotateRight(BinarySearchTreeNode **node)
{
    BinarySearchTreeNode *right, *grandchild;
    right = BinarySearchTreeNode_Right(*node);
    if ((right)->factor == 1) {
        //RR Rotation
        BinarySearchTreeNode_Right(*node) = BinarySearchTreeNode_Left(right);
        BinarySearchTreeNode_Left(right) = *node;
        (*node)->factor = 0;
        (right)->factor = 0;
        *node = right;
    }else{
        //RL rotation
        grandchild = BinarySearchTreeNode_Left(right);
        BinarySearchTreeNode_Left(right) = BinarySearchTreeNode_Right(grandchild);
        BinarySearchTreeNode_Right(grandchild) = right;
        BinarySearchTreeNode_Right(*node) = BinarySearchTreeNode_Left(grandchild);
        BinarySearchTreeNode_Left(grandchild) = *node;
        
        switch ((grandchild)->factor) {
            case -1:{
                (*node)->factor = 0;
                (right)->factor = 1;
            }
                break;
            case 0:{
                (*node)->factor = 0;
                (right)->factor = 0;
            }
                break;
            case 1:{
                (*node)->factor = -1;
                (right)->factor = 0;
            }
                break;
        }
        
        (grandchild)->factor = 0;
        *node = grandchild;
    }
}


BinarySearchTree* BinarySearchTreeCreate(int (*compare)(const void *, const void *)){
    BinarySearchTree *tree = (BinarySearchTree *)(malloc(sizeof(BinarySearchTree)));
    tree->root = NULL;
    tree->size = 0;
    tree->compare = compare;
    return tree;
}

void BinarySearchTreeDestroy(BinarySearchTree *tree){
    BinarySearchTreeNodeDestroy(tree->root);
    tree->root->data = NULL;
    free(tree->root);
    tree->root = NULL;
    tree->size = 0;
    free(tree);
    tree = NULL;
}

int BinarySearchTreeInsertLeft(BinarySearchTree *tree, BinarySearchTreeNode *node, const void *data){
    
    BinarySearchTreeNode *newNode,**position;
    
    if (node == NULL) {
        if (BinarySearchTree_Size(tree) > 0) {
            return -1;
        }
        
        position = &tree->root;
        
    }else{
        
        if (BinarySearchTreeNode_Left(node) != NULL) {
            return -1;
        }
        
        position = &node->left;
    }
    
    newNode = BinarySearchTreeNodeCreate();
    if (newNode == NULL) {
        return -1;
    }
    
    newNode->data = (void*)data;
    *position = newNode;
    tree->size++;
    return 0;
}

int BinarySearchTreeInsertRight(BinarySearchTree *tree, BinarySearchTreeNode *node, const void *data){
    BinarySearchTreeNode *newNode,**position;
    if (node == NULL) {
        if (BinarySearchTree_Size(tree) > 0) {
            return -1;
        }
        
        position = &tree->root;
        
    }else{
        if (BinarySearchTreeNode_Right(node) != NULL) {
            return -1;
        }
        
        position = &node->right;
    }
    
    newNode = BinarySearchTreeNodeCreate();
    
    if (newNode == NULL) {
        return -1;
    }
    
    newNode->data = (void*)data;
    *position = newNode;
    tree->size++;
    return 0;
}

int BinarySearchTreeInsert(BinarySearchTree *tree, BinarySearchTreeNode **node, const void *data, int *balanced){
    int cmpval, retval;
    
    if (*node == NULL) {
        tree->root = BinarySearchTreeNodeCreate();
        tree->root->data = (void *)data;
        tree->size++;
        *node = tree->root;
        return 0;
    }else{
        
        cmpval = tree->compare(data,BinarySearchTreeNode_Data(*node));
        
        if (cmpval < 0) {
            
            if (BinarySearchTreeNode_Left(*node) == NULL) {
                int result = BinarySearchTreeInsertLeft(tree, *node, data);
                if (result != 0) {
                    return -1;
                }
                
                *balanced = 0;
            }else{
                retval = BinarySearchTreeInsert(tree, &BinarySearchTreeNode_Left(*node), data, balanced);
                if (retval != 0) {
                    return retval;
                }
            }
            
            if (!(*balanced)){
                switch ((*node)->factor) {
                    case -1:{
                        BinarySearchTreeNodeRotateLeft(node);
                        *balanced = 1;
                    }
                        break;
                    case 0:{
                        (*node)->factor = -1;
                    }
                        break;
                    case 1:{
                        (*node)->factor = 0;
                        *balanced = 1;
                    }
                        break;
                }
            }
        }else if (cmpval > 0){
            if (BinarySearchTreeNode_Right(*node) == NULL) {
                retval = BinarySearchTreeInsertRight(tree, *node, data);
                if (retval != 0){
                    return -1;
                }
                *balanced = 0;
            }else{
                retval = BinarySearchTreeInsert(tree, &BinarySearchTreeNode_Right(*node), data, balanced);
                if (retval != 0) {
                    return retval;
                }
            }
            
            if (!(*balanced)){
                switch ((*node)->factor) {
                    case -1:
                    {
                        (*node)->factor = 0;
                        *balanced = 1;
                    }
                        break;
                    case 0:{
                        (*node)->factor = 1;
                    }
                        break;
                    case 1:{
                        BinarySearchTreeNodeRotateRight(node);
                        *balanced = 1;
                    }
                        break;
                }
            }
            
        } else {
            
            if (!(*node)->hidden){
                return 1;
            }else{
                (*node)->data = NULL;
                (*node)->data = (void *)data;
                (*node)->hidden = 0;
                
                *balanced = 1;
            }
        }
    }
    
    return 0;
}

int BinarySearchTreeNodeHide(BinarySearchTree *tree, BinarySearchTreeNode *node, const void* data){
    
    int cmpval, retval;
    if ((node) == NULL) {
        return -1;
    }
    cmpval = tree->compare(data, BinarySearchTreeNode_Data(node));
    if (cmpval < 0) {
        retval = BinarySearchTreeNodeHide(tree, BinarySearchTreeNode_Left(node), data);
    }else if (cmpval > 0){
        retval = BinarySearchTreeNodeHide(tree, BinarySearchTreeNode_Right(node), data);
    }else{
        node->hidden = 1;
        retval = 0;
    }
    return retval;
}

int BinarySearchTreeRemove(BinarySearchTree *tree, const void *data){
    return 0;
}
int BinarySearchTreeLookup(BinarySearchTree *tree, BinarySearchTreeNode *node, void **data){
    int cmpval, retval;
    
    if (node == NULL) {
        return -1;
    }
    
    cmpval = tree->compare(*data,BinarySearchTreeNode_Data(node));
    if (cmpval < 0) {
        retval = BinarySearchTreeLookup(tree,BinarySearchTreeNode_Left(node), data);
    }else if (cmpval > 0){
        retval = BinarySearchTreeLookup(tree,BinarySearchTreeNode_Right(node), data);
    }else{
        if (node->hidden == 0) {
            *data = BinarySearchTreeNode_Data(node);
            retval = 0;
        }else{
            return -1;
        }
    }
    
    return retval;
}

int BinarySearchTreePrintInOrder(BinarySearchTree *tree, BinarySearchTreeNode *node, const void *data){
    
    if (BinarySearchTreeNode_isEOB(node)) {
        if (tree->root) {
            node=tree->root;
        }else{
            return -1;
        }
    }
    
    if (BinarySearchTreeNode_Left(node)){
        BinarySearchTreePrintInOrder(tree, BinarySearchTreeNode_Left(node), data);
    }
    
    BinarySearchTreeNode_Print(node, data);
    
    if (BinarySearchTreeNode_Right(node)) {
        BinarySearchTreePrintInOrder(tree, BinarySearchTreeNode_Right(node), data);
    }
    
    return 0;
}




@end
