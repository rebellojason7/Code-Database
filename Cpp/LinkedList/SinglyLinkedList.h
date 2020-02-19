//
//  SinglyLinkedList.h
//  LinkedList
//
//  Created by Jason Rebello on 2/24/15.
//  Copyright (c) 2015 Jason Rebello. All rights reserved.
//
// Singly Linked List class

#ifndef LinkedList_SinglyLinkedList_h
#define LinkedList_SinglyLinkedList_h

#include <string>

using namespace std;

class SLL{
    
private:
    typedef struct node{
        int data;
        node* next;
    }* nodePtr;
    
    nodePtr head;
    nodePtr temp;
    nodePtr curr;
    nodePtr tail;
    int length=0;
    
    void searchRecursivePrivate(int, nodePtr);
    void printListPrivate(bool, nodePtr);
    void reverseUsingRecursionPrivate(nodePtr);
    
public:
    SLL();
    ~SLL();
    void addNode(int);
    void addNodeAt(int,int);
    void addNodeSorted(int);
    void delNode(int);
    void delNodeAt(int);
    void printList(string);
    void searchRecursive(int);
    void searchList(int);
    void reverseUsingIterative();
    void reverseUsingRecursion();
    void reverseUsingStack();
    void sizeOfList();
    void enqueue(int);
    void dequeue();
    int front();
    bool isEmpty();
    void push(int);
    void pop();
    int top();
    nodePtr returnHead();
    void interect(const nodePtr);
};

#endif
