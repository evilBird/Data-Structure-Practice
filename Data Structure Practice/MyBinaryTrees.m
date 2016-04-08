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

BinaryTree* BinaryTreeCreate(){
    BinaryTree *tree = (BinaryTree *)malloc(sizeof(BinaryTree));
    tree->root = NULL;
    tree->size = 0;
    return tree;
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


@end
