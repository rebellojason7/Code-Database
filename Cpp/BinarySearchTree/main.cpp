//
//  main.cpp
//  BinarySearchTree
//
//  Created by Jason Rebello on 2/26/15.
//  Copyright (c) 2015 Jason Rebello. All rights reserved.
//

// Strict/ Proper binary tree: each node can have either 2 or 0 children
// Complete binary tree : all levels except possibly the last are completely filled and all nodes are as left as possible
// Max number of nodes at level i is 2^i
// Perfect binary tree. All nodes have 2 children.
// Maximum no of nodes in a binary tree of height h = 2^0 + 2^1 + 2^2 + ... = (2^(h+1)) - 1
// 2^no of levels - 1
// h = (log(n+1) to base 2)-1
// root is at height 0, then height increase to 1...
// Height of complete binary tree = floor(logn to base 2)
// min height = logn to base 2 [O(logn)]... max height = n-1[O(n)]
// Balanced binary tree: difference between height of left and right subtree for every node is not more than k(mostly 1)
// height of empty tree = -1
// height of tree with 1 node is 0
// if tree is stored as array, then left child index = 2i+1, right child index = 2i+2
// Depth of a node is the number of edges from the root to that node.
// Breadth first = level order
// Depth first = root-left-right : preorder
// left-root-right : inorder
// left-right-root : postorder
// Binary search tree :  all elements in left subtree should be less than or equal to all elements in right sub tree

#include <iostream>
#include "BinarySearchTree.h"
#include "Trie.h"
#include <vector>
#include <unordered_map>
#include <fstream>

using namespace std;

// Union Find Algorithm --------------------------------------------------------------------------------
struct Edge{
    char vertex1;
    char vertex2;
    int weight;
    Edge(char v1, char v2, int w):vertex1(v1),vertex2(v2),weight(w){}
};

struct graph{
    vector<char> vertices;
    vector<Edge> edges;
};

unordered_map<char, char> Parent;
unordered_map<char, int> Rank;
char Find(char vertex)
{
    if(Parent[vertex] == vertex)
        return Parent[vertex];
    else
        return Find(Parent[vertex]);
}

void Union(char root1, char root2){
    if(Rank[root1] > Rank[root2])
        Parent[root2] = root1;
    else if(Rank[root2]>Rank[root1])
        Parent[root1] = root2;
    else
    {
        Parent[root1] = root2;
        Rank[root2]++;
    }
}

void makeSet(char vertex)
{
    Parent[vertex] = vertex;
    Rank[vertex] = 0;
}

// Kruskal Algorithm ---------------------------------------------------------------------------------
void kruskal(graph& g)
{
    vector<Edge> minSpanningTree;
    for(auto c: g.vertices)
        makeSet(c);
    sort(g.edges.begin(),g.edges.end(),[](Edge x, Edge y){return x.weight<y.weight;});
    // O(E*log(E))
    for(Edge e: g.edges)
    {
        char root1 = Find(e.vertex1); // E
        char root2 = Find(e.vertex2);
        if(root1 != root2)
        {
            minSpanningTree.push_back(e);
            Union(root1,root2);
        }
    }
    for(Edge e:minSpanningTree)
        cout << e.vertex1 << " -- " << e.vertex2 << "  " << e.weight << endl;
}

// Prims Algorithm -----------------------------------------------------------------------------------

struct Graph1
{
    vector<char> vertices;
    vector<Edge> edges;
    vector<pair<char, Edge>> adjacent(char u){
        vector<pair<char, Edge>> res;
        for(Edge e:edges)
        {
            if(e.vertex1 == u)
                res.push_back(make_pair(e.vertex2, e));
            else if(e.vertex2 == u)
                res.push_back(make_pair(e.vertex1, e));
        }
        return res;
    }
};

void prim(Graph1& g)
{
    unordered_map<char, char> A;
    unordered_map<char, char> parent;
    unordered_map<char, int> key;
    
    for(auto c:g.vertices){
        parent[c] = '\0';
        key[c] = INT_MAX;
    }
    key['a'] = 0; //Root
    vector<char> Q = g.vertices;
    while(!Q.empty()){ //O(V)
        char u = *std::min_element(Q.begin(), Q.end(),
                    [&](char x, char y){return key[x] < key[y];}); // O(V)
        vector<char>::iterator itr = remove(Q.begin(),Q.end(),u); // O(V)
        Q.erase(itr,Q.end()); // erase() following remove() idiom
        if(parent[u] != '\0')
            A[u] = parent[u]; // This is one edge of MST
        vector<pair<char,Edge> > adj = g.adjacent(u); // O(E)
        for(pair<char, Edge> v: adj){
            if(find(Q.begin(),Q.end(), v.first) != Q.end()){ // O(V)
                if(v.second.weight < key[v.first]){
                    parent[v.first] = u;
                    key[v.first] = v.second.weight;
                }
            }
        }
    }
        for(auto e:A){
            cout << e.first << " -- " << e.second << endl;
        }
}

int main(int argc, const char * argv[])
{
    /*
    // Test Case: Build Tree, Print Tree (Inorder, PreOrder, PostOrder), DFS, BFS
    int numOfElements = 16;
    int input=0;
    int TreeKeys[] = {50,76,21,4,32,64,15,52,14,100,83,2,3,70,87,80};
    BST myTree;
    
    cout << "Printing the tree in order\nbefore adding numbers " << endl;
    myTree.printInOrder();
    
    cout << "Printing the tree in order\nafter adding numbers " << endl;
    for(int i=0; i<numOfElements ;i ++)
    {
        myTree.addLeaf(TreeKeys[i]);
    }
    myTree.printInOrder();
    cout << endl;
    
    for(int i=0; i<numOfElements ;i ++)
    {
        myTree.printChildren(TreeKeys[i]);
        cout << endl;
    }
    
    cout << "Smallest in tree " << myTree.findSmallest() << endl;
    
    cout << "Enter a key value to delete. Enter -1 to stop the process" << endl;
    while(input != -1)
    {
        cout << "Delete Node: ";
        cin >> input;
        if(input != -1)
        {
            cout << endl;
            myTree.removeNode(input);
            myTree.printInOrder();
            cout << endl;
        }
    }
    
    myTree.printMin();
    myTree.printMax();
    cout << "Height of tree is " << myTree.findHeight() << endl;
    
    cout << "BFS: Level order : ";
    myTree.printLevelOrder();
    cout << endl;
    
    cout << "DFS: Pre order : ";
    myTree.printPreOrder();
    cout << endl;
    
    cout << "DFS: In order : ";
    myTree.printInOrder();
    cout << endl;
    
    cout << "DFS: Post order : ";
    myTree.printPostOrder();
    cout << endl;
    
    cout << "Is binary Search tree: " << myTree.isBinarySearchTree() << endl;
    */
    
    // ---------------------------------------------------------------------------------------------------
    /*
    // Test Case: Test Trie
    Trie t;
    t.insert("jason");
    t.insert("joseph");
    t.insert("rebello");
    t.insert("manchester");
    t.insert("united");
    cout << t.wordsPerPrefix("man") << endl;
     */
    
    // ---------------------------------------------------------------------------------------------------
    // Test Case: Test Graph
    char t[] = {'a','b','c','d','e','f'};
    Graph1 g;
    g.vertices = vector<char>(t, t+sizeof(t)/sizeof(t[0]));
    g.edges.push_back(Edge('a','b',3));
    g.edges.push_back(Edge('a','f',2));
    g.edges.push_back(Edge('f','b',4));
    g.edges.push_back(Edge('c','b',2));
    g.edges.push_back(Edge('c','f',1));
    g.edges.push_back(Edge('f','e',4));
    g.edges.push_back(Edge('d','e',2));
    g.edges.push_back(Edge('d','c',3));
    
    //kruskal(g);
    prim(g);
    
    ifstream openfile("test.txt");
    if(openfile.is_open())
    {
        string text;
        while(!openfile.eof())
        {
            openfile >> text;
            cout << text << endl;
        }
    }
    openfile.close();
    
    return 0;
}
