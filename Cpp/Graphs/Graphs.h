//
//  Graphs.h
//  Graphs
//
//  Created by Jason Rebello on 3/24/15.
//  Copyright (c) 2015 Jason Rebello. All rights reserved.
//

#ifndef Graphs_Graphs_h
#define Graphs_Graphs_h

#include <list>
#include <iostream>
#include <stack>

using namespace std;

class Graph
{
    int V; // Number of vertices
    list<int>* adj; // Pointer to array containing adjacency list
    void BFSUtil(int s, bool* visited);
    void DFSUtil(int s, bool* visited);
    bool isCyclicUtil(int v, bool* visited, bool* recStack);
    bool isCyclicUtilU(int v, bool* visited, int parent);
    void topologicalSortUtil(int v, bool visited[], stack<int>& S);
    
public:
    Graph(int V);
    void addEdge(int v, int w); // Adds edge in directed graph
    void addEdgeU(int v, int w); // Adds edge in undirected graph
    void BFS(int s); // Prints BFS from gives source
    void DFS(int s); // Prints DFS from gives source
    bool isCyclic(); // Check if graph has a cycle
    bool isCyclicU(); // Check if cyclic undirected
    void topologicalSort();
};

#endif
