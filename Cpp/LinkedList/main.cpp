//
//  main.cpp
//  LinkedList
//
//  Created by Jason Rebello on 2/23/15.
//  Copyright (c) 2015 Jason Rebello. All rights reserved.
//

#include <iostream>
#include "SinglyLinkedList.h"

using namespace std;

int main(int argc, const char * argv[]) {
    SLL sll1;
    
    /*
    // Test Case: Add, delete and print nodes in list
    sll1.addNode(2);
    sll1.addNode(6);
    sll1.addNode(8);
    sll1.printList();
    sll1.delNode(6);
    sll1.printList();
    sll1.addNode(7);
    sll1.addNode(9);
    sll1.printList();
    sll1.delNode(9);
    sll1.addNode(15);
    sll1.delNode(2);
    sll1.printList();
    sll1.delNode(21);
     */
    
    /*
    // Test Case: Add node at location
    sll1.addNodeAt(3,4);
    sll1.addNodeAt(2,1);
    sll1.printList();
    sll1.addNodeAt(3,4);
    sll1.addNodeAt(4,1);
    sll1.addNodeAt(5,2);
    sll1.printList();
     */
    
    /*
    // Test Case: Add node in sorted order, print list in forward and reverse order
    sll1.addNodeSorted(5);
    sll1.addNodeSorted(3);
    sll1.addNodeSorted(4);
    sll1.addNodeSorted(1);
    sll1.addNodeSorted(2);
    sll1.printList("forward"); // 0: Reverse Order ; 1: Forward Order
    sll1.delNodeAt(6);
    sll1.delNodeAt(1);
    sll1.printList("forward");
    sll1.reverseUsingIterative();
    sll1.printList("forward");
    sll1.reverseUsingRecursion();
    sll1.printList("forward");
    sll1.reverseUsingStack();
    sll1.printList("forward");
    */
    
    /*
    // Test Case: Queue using linked list
    sll1.enqueue(2);
    sll1.enqueue(4);
    sll1.enqueue(6);
    sll1.printList("forward");
    cout << "isempty " << sll1.isEmpty() << endl;
    sll1.dequeue();
    sll1.printList("forward");
    sll1.enqueue(8);
    cout << "front " << sll1.front() << endl;
    sll1.dequeue();
    sll1.printList("forward");
    sll1.dequeue();
    sll1.dequeue();
    cout << "isempty " << sll1.isEmpty() << endl;
     */
    
    // Test Case: Intersection of 2 lists
    SLL sll2;
    sll1.addNode(1);
    sll1.addNode(2);
    sll1.addNode(3);
    sll1.addNode(4);
    sll1.addNode(6);
    sll2.addNode(2);
    sll2.addNode(4);
    sll2.addNode(6);
    sll2.addNode(8);
    
    sll1.interect(sll2.returnHead());
    return 0;
}
