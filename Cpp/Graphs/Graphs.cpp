//
//  Graphs.cpp
//  Graphs
//
//  Created by Jason Rebello on 3/24/15.
//  Copyright (c) 2015 Jason Rebello. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include "Graphs.h"
#include <list>

using namespace std;

Graph::Graph(int V)
{
    this->V = V;
    adj = new list<int>[V];
}

void Graph::addEdge(int v, int w)
{
    adj[v].push_back(w); // adding w to v's list
}

void Graph::addEdgeU(int v, int w)
{
    adj[v].push_back(w);
    adj[w].push_back(v);
}

// Breadth first search ---------------------------
void Graph::BFS(int s)
{
    bool* visited = new bool[V];
    for(int i=0; i<V; i++)
        visited[i] = false;
    BFSUtil(s, visited);
    for(int i=0; i<V; i++)
        if(visited[i] == false)
            BFSUtil(i, visited);
}

void Graph::BFSUtil(int s, bool* visited)
{
    list<int> queue;
    visited[s] = true;
    queue.push_back(s);
    list<int>::iterator i;
    while(!queue.empty())
    {
        s = queue.front();
        cout << s << " ";
        queue.pop_front();
        for(i = adj[s].begin(); i!=adj[s].end(); i++)
            if(!visited[*i])
            {
                visited[*i] = true;
                queue.push_back(*i);
            }
    }
}

// Depth first search ---------------------------
void Graph::DFS(int s)
{
    bool* visited = new bool[V];
    for(int i=0; i<V; i++)
        visited[i] = false;
    DFSUtil(s, visited);
    for(int i=0; i<V; i++)
        if(visited[i] == false)
            DFSUtil(i, visited);
}

void Graph::DFSUtil(int s, bool* visited)
{
    visited[s] = true;
    cout << s << " ";
    list<int>::iterator i;
    for(i = adj[s].begin(); i!= adj[s].end(); i++)
        if(!visited[*i])
            DFSUtil(*i, visited);
}

// Detect if graph has a cycle ---------------------------
bool Graph::isCyclic()
{
    bool *visited = new bool[V];
    bool *recStack = new bool[V];
    for(int i = 0; i < V; i++)
    {
        visited[i] = false;
        recStack[i] = false;
    }
    
    // Call the recursive helper function to detect cycle in different
    // DFS trees
    for(int i = 0; i < V; i++)
        if (isCyclicUtil(i, visited, recStack))
            return true;
    
    return false;
}

bool Graph::isCyclicUtil(int v, bool* visited, bool *recStack)
{
    if(!visited[v])
    {
        visited[v] = true;
        recStack[v] = true;
        
        list<int>::iterator i;
        for(i=adj[v].begin(); i!=adj[v].end(); i++)
        {
            if(!visited[*i])
            {
                if(isCyclicUtil(*i, visited, recStack))
                    return true;
            }
            else if(recStack[*i])
                return true;
        }
    }
    recStack[v] = false;
    return false;
}

// ----- Is Cyclic Undirected -------

bool Graph::isCyclicU()
{
    bool* visited = new bool[V];
    for(int i=0; i<V; i++)
        visited[i] = false;
    for(int i=0; i<V; i++)
        if(!visited[i])
            if(isCyclicUtilU(i, visited, -1))
                return true;
    return false;
}

bool Graph::isCyclicUtilU(int v, bool *visited, int parent)
{
    visited[v] = true;
    list<int>::iterator i;
    for(i=adj[v].begin(); i != adj[v].end(); ++i)
    {
        if(!visited[*i])
        {
            if(isCyclicUtilU(*i, visited, v))
                return true;
        }
        else if(*i != parent)
            return true;
    }
    return false;
}

// ------- Topological Sorting ------
void Graph::topologicalSort()
{
    stack<int> Stack;
    bool* visited = new bool[V];
    for(int i=0; i<V; i++)
        visited[i] = false;
    for(int i=0; i<V; i++)
        if(!visited[i])
            topologicalSortUtil(i, visited, Stack);
    while(!Stack.empty())
    {
        cout << Stack.top() << " ";
        Stack.pop();
    }
}

void Graph::topologicalSortUtil(int v, bool* visited, stack<int>& Stack)
{
    visited[v] = true;
    list<int>::iterator i;
    for(i=adj[v].begin(); i!=adj[v].end(); i++)
        if(!visited[*i])
            topologicalSortUtil(*i, visited, Stack);
    Stack.push(v);
}