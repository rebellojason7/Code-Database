//
//  main.cpp
//  Graphs
//
//  Created by Jason Rebello on 3/5/15.
//  Copyright (c) 2015 Jason Rebello. All rights reserved.
//

/*
// Time Complexity BFS: O(V+E)
// Time Complexity DFS: O(V+E)
// Applications of DFS:
 1) Minimum spannign tree and all pair shortest path
 2) Detecting cycle in graph
 3) Path Finding
 4) Topological Sorting : is a linear ordering of its vertices such that for every directed edge uv from vertex u to vertex v, u comes before v in the ordering.
 5) Test if graph is bipartite: whose vertices can be divided into two disjoint sets U and V (that is, U and V are each independent sets) such that every edge connects a vertex in U to one in V. 
 6) Finding strongly connected components
 7) Solving puzzles (mazes) with only one solution
Union: O(1)
Find : O(depth)
 
 Topological sorting is only performed on DAG: O(V+E). Scheduling jobs, determining order of compilation tasks, resolving symbo dependencies in linkers
 With adjacency list representation, all vertices of a graph can be traversed in O(V+E) time using BFS
*/

#include <iostream>
#include "Graphs.h"
#include <queue>
# include <unordered_map>
#include <vector>

using namespace std;

// Check if graph is bipartite
#define V 4
#define primV 5
#define dijV 9

// ----------- Union Find ---------------
class Disjoint_set{
    unordered_map<char, char> parent;
    unordered_map<char, int> rank;
public:
    Disjoint_set();
    char find(char item);
    void Union(char set1, char set2);
};

Disjoint_set::Disjoint_set()
{
    char universe[] = {'a','b','c','d','e'};
    for(char x : universe)
    {
        parent[x] = x;
        rank[x] = 0;
    }
}

char Disjoint_set::find(char item)
{
    if(parent[item] == item)
        return item;
    else
        return find(parent[item]);
}

void Disjoint_set::Union(char set1, char set2)
{
    if(rank[set1]>rank[set2])
        parent[set2] = set1;
    else if(rank[set2] > rank[set1])
        parent[set1] = set2;
    else
    {
        parent[set1] = set2;
        rank[set2]++;
    }
}

// ----------------- Bipartite ---------------------------------

bool isBipartite(int G[][V], int src)
{
    int colorArr[V];
    for(int i=0; i<V;i++)
        colorArr[i] = -1;
    colorArr[src] = 1;
    queue<int> q;
    q.push(src);
    while(!q.empty())
    {
        int u = q.front();
        q.pop();
        for(int v=0; v<V; v++)
        {
            if(G[u][v] && colorArr[v] == -1)
            {
                colorArr[v] = 1 - colorArr[u];
                q.push(v);
            }
            else if(G[u][v] && colorArr[v] == colorArr[u])
                return false;
        }
    }
    return true;
}

// --------- Prims algorithm -------

int minKey(int key[], bool mstSet[])
{
    int minVal = INT_MAX;
    int minIdx=0;
    for(int v=0; v<primV; v++)
    {
        if(mstSet[v] == false && key[v] < minVal)
        {
            minVal = key[v];
            minIdx = v;
        }
    }
    return minIdx;
}

void printMST(int* parent, int n, int graph[primV][primV])
{
    cout << "Edge Weight\n";
    for(int i=1; i<primV; i++)
        cout << parent[i] << " - " << i << endl;
}

void primMST(int graph[primV][primV])
{
    int parent[primV]; // Store the nodes already in MST
    int key[primV]; // Stores value of edges
    bool mstSet[primV]; // Which nodes are still up for grabs
    
    for(int i=0; i<primV; i++)
    {
        key[i] = INT_MAX;
        mstSet[i] = false;
    }
    
    key[0] = 0;
    parent[0] = -1;
    
    for(int count = 0; count < primV - 1; count++)
    {
        int u = minKey(key, mstSet);
        mstSet[u] = true;
        for(int v=0; v<primV; v++)
            if(graph[u][v] && mstSet[v] == false && graph[u][v] < key[v])
            {
                parent[v] = u;
                key[v] = graph[u][v];
            }
    }
    printMST(parent, primV, graph);
}

// ---- Kruskals Algorithm -------

unordered_map<char, char> parentk;
unordered_map<char, int> rankk;

char Find(char vertex)
{
    if(parentk[vertex] == vertex)
        return vertex;
    else
        return parentk[vertex];
}

void Union(char root1, char root2)
{
    if(rankk[root1]>rankk[root2])
        parentk[root2] = root1;
    else if(rankk[root2]>rankk[root1])
        parentk[root1] = root2;
    else
    {
        parentk[root1] = root2;
        parentk[root2]++;
    }
}

struct Edge
{
    char vertex1;
    char vertex2;
    int weight;
    Edge(char v1, char v2, int w):vertex1(v1),vertex2(v2),weight(w){}
};

struct GraphK{
    vector<char> vertices;
    vector<Edge> edges;
};


void makeSet(char vertex)
{
    parentk[vertex] = vertex;
    rankk[vertex] = 0;
}

void kruskal(GraphK& g)
{
    vector<Edge> A; // stores the final min spanning tree
    for(auto c: g.vertices)
        makeSet(c);
    sort(g.edges.begin(),g.edges.end(),[](Edge x, Edge y){return x.weight<y.weight;});
    for(Edge e : g.edges)
    {
        char root1 = Find(e.vertex1);
        char root2 = Find(e.vertex2);
        if(root1 != root2)
        {
            A.push_back(e);
            Union(root1,root2);
        }
    }
    
}

// ---- Dijkstras algorithm O(v^2).. doesnt handle negative weights-------

int minDist(int* dist, int* sptSet)
{
    int minVal = INT_MAX;
    int minIdx = 0;
    for(int i=0; i<dijV; i++)
        if(!sptSet[i] && dist[i]<=minVal)
        {
            minVal = dist[i];
            minIdx = i;
        }
    return minIdx;
}

void printSolution(int dist[], int n)
{
    printf("Vertex   Distance from Source\n");
    for (int i = 0; i < dijV; i++)
        printf("%d \t\t %d\n", i, dist[i]);
}

void dijkstra(int graphD[dijV][dijV], int src)
{
    int dist[dijV];
    int sptSet[dijV];
    for(int i=0; i<dijV; i++)
    {
        dist[i] = INT_MAX;
        sptSet[i] = false;
    }
    dist[src] = 0;
    for(int count = 0; count < dijV-1; count++)
    {
        int u = minDist(dist,sptSet);
        sptSet[u] = true;
        for(int v=0; v<dijV; v++)
            if(!sptSet[v] && graphD[u][v] && dist[u] != INT_MAX && dist[u]+graphD[u][v] < dist[v])
                dist[v] = dist[u] + graphD[u][v];
    }
    printSolution(dist,dijV);
}

// ------- Bellman-Ford Algorithm -------
struct EdgeBF
{
    int src, dest, weight;
};

struct GraphBF
{
    int Vbf,Ebf;
    EdgeBF* edge;
    
};

GraphBF* createGraph(int Vbf, int Ebf)
{
    GraphBF* graph = new GraphBF;
    graph->Vbf = Vbf;
    graph->Ebf = Ebf;
    graph->edge = new EdgeBF[Ebf];
    return graph;
}

void printArr(int dist[], int n)
{
    printf("Vertex   Distance from Source\n");
    for (int i = 0; i < n; ++i)
        printf("%d \t\t %d\n", i, dist[i]);
}

void BellmanFord(struct GraphBF* graph, int src)
{
    int Vbf = graph->Vbf;
    int E = graph->Ebf;
    int dist[V];
    
    // Step 1: Initialize distances from src to all other vertices as INFINITE
    for (int i = 0; i < Vbf; i++)
        dist[i]   = INT_MAX;
    dist[src] = 0;
    
    // Step 2: Relax all edges |V| - 1 times. A simple shortest path from src
    // to any other vertex can have at-most |V| - 1 edges
    for (int i = 1; i <= Vbf-1; i++)
    {
        for (int j = 0; j < E; j++)
        {
            int u = graph->edge[j].src;
            int v = graph->edge[j].dest;
            int weight = graph->edge[j].weight;
            if (dist[u] != INT_MAX && dist[u] + weight < dist[v])
                dist[v] = dist[u] + weight;
        }
    }
    
    // Step 3: check for negative-weight cycles.  The above step guarantees
    // shortest distances if graph doesn't contain negative weight cycle.
    // If we get a shorter path, then there is a cycle.
    for (int i = 0; i < E; i++)
    {
        int u = graph->edge[i].src;
        int v = graph->edge[i].dest;
        int weight = graph->edge[i].weight;
        if (dist[u] != INT_MAX && dist[u] + weight < dist[v])
            printf("Graph contains negative weight cycle");
    }
    
    printArr(dist, Vbf);
    
    return;
}

int main(int argc, const char * argv[]) {

    Graph gDirected(4);
    gDirected.addEdge(0, 1);
    gDirected.addEdge(0, 2);
    gDirected.addEdge(1, 2);
    gDirected.addEdge(2, 0);
    gDirected.addEdge(2, 3);
    gDirected.addEdge(3, 3);
    
    cout << "Following is Breadth First Traversal (starting from vertex 2) \n";
    gDirected.BFS(2);
    
    cout << "\nFollowing is Depth First Traversal (starting from vertex 2) \n";
    gDirected.DFS(2);
    
    cout << endl;
    if(gDirected.isCyclic())
        cout << "Graph contains cycle\n";
    else
        cout << "Graph doesn't contain cycle\n";
    
    // -------- Undirected Graph -------
    cout << "\nTesting Undirected Graph\n";
    Graph g1(5);
    g1.addEdgeU(1, 0);
    g1.addEdgeU(2, 1);
    g1.addEdgeU(2, 0);
    g1.addEdgeU(0, 3);
    g1.addEdgeU(3, 4);
    g1.isCyclicU()? cout << "Graph contains cycle\n":
    cout << "Graph doesn't contain cycle\n";
    
    Graph g2(3);
    g2.addEdgeU(0, 1);
    g2.addEdgeU(1, 2);
    g2.isCyclicU()? cout << "Graph contains cycle\n":
    cout << "Graph doesn't contain cycle\n";
    
    // ----- Topological Sorting -------
    // Create a graph given in the above diagram
    Graph g(6);
    g.addEdge(5, 2);
    g.addEdge(5, 0);
    g.addEdge(4, 0);
    g.addEdge(4, 1);
    g.addEdge(2, 3);
    g.addEdge(3, 1);
    
    cout << "\nFollowing is a Topological Sort of the given graph \n";
    g.topologicalSort();
    
    // Check if graph is bipartite
    int G[][V] = {{0, 1, 0, 1},
        {1, 0, 1, 0},
        {0, 1, 0, 1},
        {1, 0, 1, 0}
    };
    cout << "\n\nis Bipartite ?" <<endl;
    isBipartite(G, 0) ? cout << " Yes" : cout << "No";
    
    Disjoint_set ds;
    ds.find('c');
    ds.Union('c', 'a');
    ds.find('c');
    ds.Union('a','b');
    
    // ---- Prims algorithm --------
    /* Let us create the following graph
     2    3
     (0)--(1)--(2)
     |   / \   |
    6| 8/   \5 |7
     | /     \ |
     (3)-------(4)
          9          */
    int graph[primV][primV] = { {0, 2, 0, 6, 0},
                                {2, 0, 3, 8, 5},
                                {0, 3, 0, 0, 7},
                                {6, 8, 0, 0, 9},
                                {0, 5, 7, 9, 0},
    };
    
    // Print the solution
    primMST(graph);
    
    // ----- Kruskals Algorithm -----
    char t[] = {'a','b','c','d','e'};
    GraphK gk;
    gk.vertices = vector<char>(t,t+sizeof(t)/sizeof(t[0]));
    gk.edges.push_back(Edge('a','b',4));
    gk.edges.push_back(Edge('a','f',2));
    gk.edges.push_back(Edge('f','b',5));
    gk.edges.push_back(Edge('c','b',6));
    gk.edges.push_back(Edge('c','f',1));
    gk.edges.push_back(Edge('f','e',4));
    gk.edges.push_back(Edge('d','e',2));
    gk.edges.push_back(Edge('d','c',3));
    
    kruskal(gk);
    
    // ------ Dijkstras algorithm (shortest path) ----
    cout << "\n\n Dijkstras algorithm" << endl;
    int graphD[dijV][dijV] = {{0, 4, 0, 0, 0, 0, 0, 8, 0},
        {4, 0, 8, 0, 0, 0, 0, 11, 0},
        {0, 8, 0, 7, 0, 4, 0, 0, 2},
        {0, 0, 7, 0, 9, 14, 0, 0, 0},
        {0, 0, 0, 9, 0, 10, 0, 0, 0},
        {0, 0, 4, 0, 10, 0, 2, 0, 0},
        {0, 0, 0, 14, 0, 2, 0, 1, 6},
        {8, 11, 0, 0, 0, 0, 1, 0, 7},
        {0, 0, 2, 0, 0, 0, 6, 7, 0}
    };
    
    dijkstra(graphD, 0);
    
    // -------- Belman-Ford shortest path ----------
    int Vbf = 5;  // Number of vertices in graph
    int E = 8;  // Number of edges in graph
    struct GraphBF* graphbf = createGraph(Vbf, E);
    
    // add edge 0-1 (or A-B in above figure)
    graphbf->edge[0].src = 0;
    graphbf->edge[0].dest = 1;
    graphbf->edge[0].weight = -1;
    
    // add edge 0-2 (or A-C in above figure)
    graphbf->edge[1].src = 0;
    graphbf->edge[1].dest = 2;
    graphbf->edge[1].weight = 4;
    
    // add edge 1-2 (or B-C in above figure)
    graphbf->edge[2].src = 1;
    graphbf->edge[2].dest = 2;
    graphbf->edge[2].weight = 3;
    
    // add edge 1-3 (or B-D in above figure)
    graphbf->edge[3].src = 1;
    graphbf->edge[3].dest = 3;
    graphbf->edge[3].weight = 2;
    
    // add edge 1-4 (or A-E in above figure)
    graphbf->edge[4].src = 1;
    graphbf->edge[4].dest = 4;
    graphbf->edge[4].weight = 2;
    
    // add edge 3-2 (or D-C in above figure)
    graphbf->edge[5].src = 3;
    graphbf->edge[5].dest = 2;
    graphbf->edge[5].weight = 5;
    
    // add edge 3-1 (or D-B in above figure)
    graphbf->edge[6].src = 3;
    graphbf->edge[6].dest = 1;
    graphbf->edge[6].weight = 1;
    
    // add edge 4-3 (or E-D in above figure)
    graphbf->edge[7].src = 4;
    graphbf->edge[7].dest = 3;
    graphbf->edge[7].weight = -3;
    
    BellmanFord(graphbf, 0);
    return 0;
}
