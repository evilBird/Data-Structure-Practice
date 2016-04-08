//
//  MyBinaryTrees.h
//  Data Structure Practice
//
//  Created by Travis Henspeter on 4/6/16.
//  Copyright © 2016 birdSound. All rights reserved.
//

#import <Foundation/Foundation.h>

#define BinaryTree_Size(tree)   ((tree)->size)
#define BinaryTree_Root(tree)   ((tree)->root)
#define BinaryTree_Left(node)   ((node)->left)
#define BinaryTree_Right(node)  ((node)->right)

@interface MyBinaryTrees : NSObject

typedef struct MyBinaryTreeNode{
    void *data;
    struct MyBinaryTreeNode *left;
    struct MyBinaryTreeNode *right;
}BinaryTreeNode;

BinaryTreeNode* BinaryTreeNodeCreate();

typedef struct MyBinaryTree{
    int             size;
    int             (*compare)(const void *key1, const void *key2);
    BinaryTreeNode  *root;
}BinaryTree;

BinaryTree* BinaryTreeCreate();
void BinaryTreeDestroy(BinaryTree *tree);
int BinaryTreeInsertLeft(BinaryTree *tree, BinaryTreeNode *node, const void *data);
int BinaryTreeInsertRight(BinaryTree *tree, BinaryTreeNode *node, const void *data);
void BinaryTreeRemoveLeft(BinaryTree *tree, BinaryTreeNode *node);
void BinaryTreeRemoveRight(BinaryTree *tree, BinaryTreeNode *node);
int BinaryTreeMerge(BinaryTree *merge, BinaryTree *left, BinaryTree *right, const void *data);

@end
