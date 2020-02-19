#include "DisjointSet.h"
#include <iostream>
#include <string>

using namespace std;

// Constructor --------------------------------------------------------------------------------------

DisjointSet::DisjointSet()
{
    char universe[] = {'a','b','c','d','e'};
    int uniSize = sizeof(universe)/sizeof(universe[0]);
    for(int i=0; i<uniSize; i++)
    {
        parent[universe[i]] = universe[i];
        rank[universe[i]] = 0;
    }
    parent['d'] = 'b';
    rank['b'] = 1;
}

// Find parent of node -----------------------------------------------------------------------------------

char DisjointSet::find(char item)
{
    if(parent[item]==item)
        return item;
    else
        return find(parent[item]);
}

// Join two sets --------------------------------------------------------------------------------------

void DisjointSet::Union(char set1, char set2)
{
    if(rank[set1]>rank[set2])
    {
        parent[set2] = set1;
    }
    else if(rank[set2]>rank[set1])
        parent[set1] = set2;
    else
    {
        parent[set1] = set2;
        rank[set2]++;
    }
}