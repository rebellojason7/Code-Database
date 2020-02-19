//
//  BinarySearchTree.h
//  BinarySearchTree
//
//  Created by Jason Rebello on 2/26/15.
//  Copyright (c) 2015 Jason Rebello. All rights reserved.
//
//  Binary Search Tree Header file

#ifndef BinarySearchTree_BinarySearchTree_h
#define BinarySearchTree_BinarySearchTree_h

#include <iostream>

class BST
{
    typedef struct node{
        int key;
        node* left;
        node* right;
    }* nodePtr;
    
    nodePtr root;
    nodePtr curr;
    nodePtr temp;
    
    void addLeafPrivate(int, nodePtr);
    void printLevelOrderPrivate(nodePtr);
    void printPreOrderPrivate(nodePtr);
    void printInOrderPrivate(nodePtr);
    void printPostOrderPrivate(nodePtr);
    nodePtr returnNodePrivate(int, nodePtr);
    nodePtr returnNode(int);
    nodePtr createLeaf(int);
    int findSmallestPrivate(nodePtr);
    void removeNodePrivate(int, nodePtr);
    void removeRootMatch();
    void removeMatch(nodePtr, nodePtr, bool);
    // first nodePtr: is for parent of match
    // second nodePtr: is the match found
    // third bool if true matching node is left child of parent
    void removeSubtree(nodePtr);
    int findHeightPrivate(nodePtr);
    bool isBinarySearchTreePrivate(nodePtr, int, int);
    nodePtr deleteNodePrivate(nodePtr,int);
    nodePtr getSuccessorPrivate(nodePtr,int);
    
public:
    BST();
    ~BST();
    void addLeaf(int);
    void printLevelOrder(); // BFS time: O(n) , space : best O(1), worst/avg O(n)
    void printPreOrder(); // DFS time O(n) , space : worst O(n), best avg : O(logn)
    void printInOrder(); // DFS
    void printPostOrder(); // DFS
    int returnRootKey();
    void printChildren(int);
    int findSmallest();
    void removeNode(int);
    void printMin();
    void printMax();
    int findHeight();
    bool isBinarySearchTree(); // time O(n) In order tells us if it is a BST
    void deleteNode(int);
    void getSuccessor(int);
};

#endif
