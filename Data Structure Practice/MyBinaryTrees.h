//
//  MyBinaryTrees.h
//  Data Structure Practice
//
//  Created by Travis Henspeter on 4/6/16.
//  Copyright © 2016 birdSound. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface MyBinaryTrees : NSObject

typedef struct MyBinaryTreeNode{
    void *data;
    struct MyBinaryTreeNode *left;
    struct MyBinaryTreeNode *right;
}BinaryTreeNode;

typedef struct MyBinaryTree{
    BinaryTreeNode  *root;
}BinaryTree;


@end
