//
//  MyBinarySearchTrees.h
//  Data Structure Practice
//
//  Created by Travis Henspeter on 4/6/16.
//  Copyright © 2016 birdSound. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "MySinglyLinkedLists.h"

@interface MyBinarySearchTrees : NSObject

typedef struct BinarySearchTreeNode_{
    void                            *data;
    struct BinarySearchTreeNode_    *left;
    struct BinarySearchTreeNode_    *right;
    int                             factor;
    int                             hidden;
}BinarySearchTreeNode;

int BinarySearchTreeNode_CompareFloats(const void *key1, const void *key2);
int BinarySearchTreeNode_CompareInts(const void *key1, const void *key2);
void BinarySearchTreeNode_Print(BinarySearchTreeNode *node, const void *data);
BinarySearchTreeNode* BinarySearchTreeNodeCreate();

void BinarySearchTreeNodeDestroy(BinarySearchTreeNode *node);
void BinarySearchTreeNodeRotateLeft(BinarySearchTreeNode **node);
void BinarySearchTreeNodeRotateRight(BinarySearchTreeNode **node);


#define BinarySearchTreeNode_isLeaf(node)       ((((node)->left == NULL) && ((node)->right == NULL)) ? 1 : 0 )
#define BinarySearchTreeNode_isEOB(node)        (((node) == NULL) ? 1 : 0 )
#define BinarySearchTreeNode_Data(node)         ((node)->data)
#define BinarySearchTreeNode_Left(node)         ((node)->left)
#define BinarySearchTreeNode_Right(node)        ((node)->right)


typedef struct BinarySearchTree_{
    BinarySearchTreeNode            *root;
    int                              size;
    int                             (*compare)(const void *key1, const void *key2);
    
}BinarySearchTree;

BinarySearchTree* BinarySearchTreeCreate(int (*compare)(const void *, const void *));
void BinarySearchTreeDestroy(BinarySearchTree *tree);

int BinarySearchTreeInsert(BinarySearchTree *tree, BinarySearchTreeNode **node, const void *data, int *balanced);
int BinarySearchTreeRemove(BinarySearchTree *tree, const void *data);
int BinarySearchTreeLookup(BinarySearchTree *tree, BinarySearchTreeNode *node, void **data);
int BinarySearchTreePrintInOrder(BinarySearchTree *tree, BinarySearchTreeNode *node, const void *data);
void BinarySearchTreePrintVisual(BinarySearchTree *tree, void (*formatData)(char *, const void *));

#define BinarySearchTree_Size(tree)     ((tree)->size)
#define BinarySearchTree_Root(tree)     ((tree)->root)

@end
