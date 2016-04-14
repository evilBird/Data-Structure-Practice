//
//  MyBinaryTrees.m
//  Data Structure Practice
//
//  Created by Travis Henspeter on 4/6/16.
//  Copyright © 2016 birdSound. All rights reserved.
//

#import "MyBinaryTrees.h"

@implementation MyBinaryTrees

BinaryTreeNode* BinaryTreeNodeCreate(){
    BinaryTreeNode *node = (BinaryTreeNode *)malloc(sizeof(BinaryTreeNode));
    node->left = NULL;
    node->right = NULL;
    node->data = NULL;
    return node;
}

int BinaryTreeNodePrint(BinaryTreeNode *node, const void *info){
    float *ptr = (float *)(node->data);
    printf("\n%.3f",*ptr);
    return 0;
}

BinaryTree* BinaryTreeCreate(){
    BinaryTree *tree = (BinaryTree *)malloc(sizeof(BinaryTree));
    tree->root = NULL;
    tree->size = 0;
    return tree;
}

int BinaryTreeNodeCompareFloatData(void *data1, void *data2){
    float f1 = (*(float *)data1);
    float f2 = (*(float *)data2);
    return (f1-f2);
}

int BinaryTreePrintNode(BinaryTree *tree, BinaryTreeNode *node, const void *info){
    float *ptr = (float *)(node->data);
    printf("\n%.3f",*ptr);
    return -1;
}

int BinaryTreeInsertLeft(BinaryTree *tree, BinaryTreeNode *node, const void *data){
    
    BinaryTreeNode *newNode,**position;
    if (node == NULL) {
        if (BinaryTree_Size(tree) > 0) {
            return -1;
        }
        
        position = &tree->root;
    }else{
        if (BinaryTree_Left(node) != NULL) {
            return -1;
        }
        
        position = &node->left;
    }
    
    newNode = BinaryTreeNodeCreate();
    if (newNode == NULL) {
        return -1;
    }
    
    newNode->data = (void*)data;
    *position = newNode;
    tree->size++;
    return 0;
}

int BinaryTreeInsertRight(BinaryTree *tree, BinaryTreeNode *node, const void *data){
    BinaryTreeNode *newNode,**position;
    if (node == NULL) {
        if (BinaryTree_Size(tree) > 0) {
            return -1;
        }
        
        position = &tree->root;
        
    }else{
        if (BinaryTree_Right(node) != NULL) {
            return -1;
        }
        
        position = &node->right;
    }
    
    newNode = BinaryTreeNodeCreate();
    
    if (newNode == NULL) {
        return -1;
    }
    
    newNode->data = (void*)data;
    *position = newNode;
    tree->size++;
    return 0;
}

int BinaryTreeInsert(BinaryTree *tree, BinaryTreeNode *node, const void *data){
    
    if (!node){
        if (tree->size == 0 && tree->root == NULL) {
            BinaryTreeNode *root = BinaryTreeNodeCreate();
            root->data = (void *)data;
            tree->root = root;
            tree->size++;
            return 0;
        }else{
            return -1;
        }
    }
    
    int compare = BinaryTreeNodeCompareFloatData((void *)data, node->data);
    
    if (compare <= 0) {
        if (node->left){
            return BinaryTreeInsert(tree, node->left, data);
        }else{
            return BinaryTreeInsertLeft(tree, node, data);
        }
    }else{
        if (node->right) {
            return BinaryTreeInsert(tree, node->right, data);
        }else{
            return BinaryTreeInsertRight(tree, node, data);
        }
    }
}

void BinaryTreeRemoveLeft(BinaryTree *tree, BinaryTreeNode *node){
    
    BinaryTreeNode **position;
    if (BinaryTree_Size(tree) == 0) {
        return;
    }
    if (node==NULL) {
        position = &tree->root;
    }else{
        position = &node->left;
    }
    
    if (*position != NULL) {
        free(*position);
        *position = NULL;
    }
    
    tree->size--;
}

void BinaryTreeRemoveRight(BinaryTree *tree, BinaryTreeNode *node){
    BinaryTreeNode **position;
    if (BinaryTree_Size(tree) == 0) {
        return;
    }
    if (node==NULL) {
        position = &tree->root;
    }else{
        position = &node->right;
    }
    
    if (*position != NULL) {
        free(*position);
        *position = NULL;
    }
    
    tree->size--;
}

int BinaryTreeRemove(BinaryTree *tree, BinaryTreeNode *node, const void *data){
    
    if (BinaryTree_Size(tree) == 0) {
        return -1;
    }
    
    int compare = BinaryTreeNodeCompareFloatData(node, (void*)data);
    
    if (compare <= 0 && node->left) {
        int compareL = BinaryTreeNodeCompareFloatData(node->left, (void*)data);
        if (compareL == 0) {
            BinaryTreeRemoveLeft(tree, node);
            return 0;
        }else {
            return BinaryTreeRemove(tree, node->left, data);
        }
    }else if (compare > 0 && node->right){
        int compareR = BinaryTreeNodeCompareFloatData(node->right, (void *)data);
        if (compareR == 0) {
            BinaryTreeRemoveRight(tree,node);
            return 0;
        }else{
            return BinaryTreeRemove(tree, node->right, data);
        }
    }
    
    return -1;
}

void BinaryTreeDestroy(BinaryTree *tree){
    BinaryTreeRemoveLeft(tree, NULL);
    free(tree);
    tree = NULL;
}

int BinaryTreeMerge(BinaryTree *merge, BinaryTree *left, BinaryTree *right, const void *data){
    
    merge = BinaryTreeCreate();
    if (BinaryTreeInsertLeft(merge, NULL, data) != 0) {
        BinaryTreeDestroy(merge);
        return -1;
    }
    BinaryTree_Root(merge)->left = BinaryTree_Root(left);
    BinaryTree_Root(merge)->right = BinaryTree_Root(right);
    merge->size = merge->size + BinaryTree_Size(left) + BinaryTree_Size(right);
    
    left->root = NULL;
    left->size = 0;
    right->root = NULL;
    right->size = 0;
    
    return 0;
}

int BinaryTreeTraverseInOrder(BinaryTree *tree,
                              BinaryTreeNode *node,
                              const void *data,
                              int (*function)(BinaryTree *, BinaryTreeNode *, const void *))
{
    if (!node){
        return function(tree, node, data);
    }
    
    if (BinaryTree_Left(node)){
        
        if (BinaryTreeTraverseInOrder(tree, BinaryTree_Left(node),data, function) == 0) {
            return 0;
        }
    }
    
    if (function(tree, node, data) == 0){
        return 0;
    };
    
    if (BinaryTree_Right(node)) {
        if (BinaryTreeTraverseInOrder(tree, BinaryTree_Right(node),data, function) == 0) {
            return 0;
        }
    }
    
    return -1;
}

int BinaryTreeTraversePreOrder(BinaryTree *tree,
                               BinaryTreeNode *node,
                               const void *data,
                               int (*function)(BinaryTree *, BinaryTreeNode *, const void *)){
    
    if (!node){
        return function(tree, node, data);
    }
    
    if (BinaryTreeNode_isLeaf(node)){
        return function(tree, node, data);
    }
    
    if (function(tree,node,data) == 0){
        return 0;
    };
    
    if (BinaryTree_Left(node)) {
        if (BinaryTreeTraversePreOrder(tree, BinaryTree_Left(node), data, function)==0){
            return 0;
        };
    }
    
    if (BinaryTree_Right(node)) {
        if (BinaryTreeTraversePreOrder(tree, BinaryTree_Right(node), data, function)==0){
            return 0;
        };
    }
    
    return -1;
}

int BinaryTreeTraversePostOrder(BinaryTree *tree,
                                BinaryTreeNode *node,
                                const void *data,
                                int (*function)(BinaryTree *, BinaryTreeNode *, const void *)){
    
    if (!node){
        return function(tree, node, data);
    }
    
    if (BinaryTreeNode_isLeaf(node)){
        return function(tree, node, data);
    }
    
    if (BinaryTree_Left(node)) {
        if (BinaryTreeTraversePostOrder(tree, BinaryTree_Left(node), data,function)==0){
            return 0;
        };
    }
    
    if (BinaryTree_Right(node)) {
        if (BinaryTreeTraversePostOrder(tree, BinaryTree_Right(node), data,function)==0){
            return 0;
        };
    }
    
    if (function(tree, node,data)==0){
        return 0;
    };
    
    return -1;
}


void BinaryTreePrintInOrder(BinaryTree *tree){
    printf("\nprint tree in order");
    BinaryTreeTraverseInOrder(tree, tree->root, NULL,BinaryTreePrintNode);
    printf("\n");
}

void BinaryTreePrintPreOrder(BinaryTree *tree){
    printf("\nprint tree pre order");
    BinaryTreeTraversePreOrder(tree, tree->root, NULL,BinaryTreePrintNode);
    printf("\n");
}

void BinaryTreePrintPostOrder(BinaryTree *tree){
    printf("\nprint tree post order");
    BinaryTreeTraversePostOrder(tree,tree->root, NULL,BinaryTreePrintNode);
    printf("\n");
}

@end
