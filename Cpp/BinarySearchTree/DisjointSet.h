//
//  DisjointSet.h
//  BinarySearchTree
//
//  Created by Jason Rebello on 3/12/15.
//  Copyright (c) 2015 Jason Rebello. All rights reserved.
//
//  Disjoint set test header file

#ifndef BinarySearchTree_DisjointSet_h
#define BinarySearchTree_DisjointSet_h
#include <iostream>
#include <unordered_map>
using namespace std;

class DisjointSet{
    unordered_map<char, char> parent;
    unordered_map<char, int> rank; // record the depth of tree
public:
    DisjointSet();
    char find(char);
    void Union(char, char);
};

#endif
