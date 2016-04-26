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

int BinarySearchTreeNode_CompareInts(const void *key1, const void *key2){
    return (*(int*)key1)-(*(int*)key2);
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


SinglyLinkedList* NodeLevelList(BinarySearchTree *tree, SinglyLinkedList *prevLevelList){
    
    SinglyLinkedList *nodeLevelList = SinglyLinkedListCreate(NULL);
    
    if (prevLevelList == NULL) {
        
        SinglyLinkedListAppend(nodeLevelList, (void *)(tree->root));
        
    }else{
        
        SinglyLinkedListElement *e = prevLevelList->head;
        
        while (1) {
            
            BinarySearchTreeNode *node = (BinarySearchTreeNode *)(e->data);
            
            if (node->left) {
                SinglyLinkedListAppend(nodeLevelList, (void*)(node->left));
            }
            
            if (node->right) {
                SinglyLinkedListAppend(nodeLevelList, (void*)(node->right));
            }
            
            if (e->next == NULL) {
                break;
            }
            
            e = e->next;
            
        }
        
    }
    
    return nodeLevelList;
}

int FindNodeHt(BinarySearchTreeNode *node){
    
    if (node == NULL) {
        return -1;
    }
    
    int leftHt = FindNodeHt(node->left);
    int rightHt = FindNodeHt(node->right);
    
    if (leftHt > rightHt) {
        return (leftHt + 1);
    }else{
        return (rightHt + 1);
    }
}

void BinarySearchTreePrintVisual(BinarySearchTree *tree, void (*formatData)(char *, const void *)){
    printf("\n\n");
    
    int ht = FindNodeHt(tree->root);
    int maxNodesPerLevel = (int)powf(2.0, (float)ht);
    int spacesPerNode = 4;
    int minPadding = 2;
    int totalWidth = (maxNodesPerLevel * spacesPerNode) + ((maxNodesPerLevel-1)*minPadding);
    int currentLevel = 0;
    SinglyLinkedList *prevList = NULL;
    SinglyLinkedList *nodeList = NodeLevelList(tree, prevList);
    int *nextLevelLayout = NULL;
    
    while (currentLevel < ht) {
        
        if (nextLevelLayout == NULL){
            
            int center = totalWidth/2;
            int start = center-(spacesPerNode/2);
            
            printf("\n");
            int i = 0;
            
            for (; i < start; i++) {
                printf(".");
            }
            
            SinglyLinkedListElement *e = nodeList->head;
            BinarySearchTreeNode *node = (BinarySearchTreeNode *)e->data;
            char fmt[10];
            formatData(fmt,node->data);
            printf("[%s]",fmt);
            i+=spacesPerNode;
            int maxNodesNextLevel = (int)powf(2.0, (float)(currentLevel+1));
            int leftBranchCenter = start-1;
            int leftCenter = leftBranchCenter - (spacesPerNode/2);
            int rightBranchCenter = i;
            int rightCenter = rightBranchCenter - (spacesPerNode/2);
            
            nextLevelLayout = (int*)malloc(sizeof(int) * (maxNodesNextLevel + 1));
            i = 0;
            
            for (; i < leftBranchCenter; i++) {
                printf(".");
            }
            
            if (node->left) {
                nextLevelLayout[0] = leftCenter;
                printf("/");
            }else{
                nextLevelLayout[0] = -1;
                printf(".");
            }
            
            i++;
            
            for (; i < rightBranchCenter; i++) {
                printf(".");
            }
            
            if (node->right) {
                nextLevelLayout[1] = rightCenter;
                printf("\\");
            }else{
                nextLevelLayout[1] = -1;
                printf(".");
            }
            
            i++;
            
        }else{
            
            int maxNodesThisLevel = (int)powf(2.0, (float)(currentLevel));
            int maxNodesNextLevel = ( currentLevel < ht ) ? ( maxNodesThisLevel * 2 ) : ( 0 );
            int *temp = NULL;
            temp = (maxNodesNextLevel > 0) ? ((int*)malloc(sizeof(int) * (maxNodesNextLevel + 1))) : ( NULL );
            int i = 0;
            printf("\n");
            SinglyLinkedListElement *e = nodeList->head;
            
            for (int idx = 0; idx < maxNodesThisLevel; idx++) {
                int thisCenter = nextLevelLayout[i];
                int thisStart = thisCenter-(spacesPerNode/2);
                int nextStart = -1;
                int nextStop = -1;
                
                if (thisCenter > totalWidth) {
                    break;
                }
                
                if (thisCenter >= 0) {
                    for (; i<thisStart; i++) {
                        printf(".");
                    }
                    
                    BinarySearchTreeNode *node = (BinarySearchTreeNode *)e->data;
                    
                    char fmt[10];
                    formatData(fmt,node->data);
                    printf("[%s]",fmt);
                    i+=spacesPerNode;
                    if (node->left) {
                        nextStart = (thisStart-1);
                    }
                    
                    if(node->right){
                        nextStop = i+1;
                    }
                    
                    
                    if (e->next) {
                        e = e->next;
                    }
                }
                
                if (temp != NULL){
                    int tempIdx = idx*2;
                    temp[tempIdx] = nextStart;
                    tempIdx++;
                    temp[tempIdx] = nextStop;
                }
                
            }
            
            if (temp != NULL) {
                printf("\n");
                i = 0;
                
                for (int idx = 0; idx<maxNodesThisLevel; idx++) {
                    
                    int leftIdx = idx*2;
                    int rightIdx = leftIdx+1;
                    int left = temp[leftIdx];
                    int right = temp[rightIdx];
                    
                    if (left > totalWidth || right > totalWidth){
                        break;
                    }
                    
                    if (left > 0) {
                        for (; i<left; i++) {
                            printf(".");
                        }
                        temp[leftIdx] = (left-(spacesPerNode/2));
                        printf("/");
                    }
                    
                    if (right>0) {
                        for (; i<right; i++) {
                            printf(".");
                        }
                        printf("\\");
                        temp[rightIdx] = (rightIdx-(spacesPerNode/2));
                    }
                }
                
                nextLevelLayout = temp;
            }
            
        }
        
        prevList = nodeList;
        currentLevel ++;

        if (currentLevel < ht) {
            nodeList = NodeLevelList(tree, prevList);
        }
    }
    
    printf("\n\n");
    
}



@end
