//
//  Trie.h
//  BinarySearchTree
//
//  Created by Jason Rebello on 3/12/15.
//  Copyright (c) 2015 Jason Rebello. All rights reserved.
//
//  Trie Header file

#ifndef BinarySearchTree_Trie_h
#define BinarySearchTree_Trie_h

#include <string>
#include <iostream>

using namespace std;

const int ALPHABET_SIZE = 26;

class Trie
{
    typedef struct node
    {
        bool isEnd; // Whether the node is an end point of the word
        int prefixCount; // number of words with given prefix
        node* child[ALPHABET_SIZE];
        
    }* nodePtr;
    
    nodePtr head;
    
public:
    Trie();
    void insert(string word);
    bool search(string word);
    int wordsPerPrefix(string prefix);
};

#endif
