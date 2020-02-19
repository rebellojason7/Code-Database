#include "Trie.h"
#include <iostream>
#include <string>

using namespace std;

// Constructor --------------------------------------------------------------------------------------

Trie::Trie()
{
    head = new node();
    head->prefixCount = 0;
    head->isEnd = false;
}

// Insert into Trie --------------------------------------------------------------------------------------

void Trie::insert(string word)
{
    nodePtr current = head;
    current->prefixCount++;
    for(unsigned int i=0; i<word.length(); i++)
    {
        int letter = (int)word[i] - (int)'a';
        if(current->child[letter] == NULL)
            current->child[letter] = new node();
        current->child[letter]->prefixCount++;
        current = current->child[letter];
    }
    current->isEnd = true;
}

// Search Trie --------------------------------------------------------------------------------------

bool Trie::search(string word)
{
    nodePtr current = head;
    for(unsigned int i=0; i<word.length(); i++)
    {
        int letter = (int)word[i]-(int)'a';
        if(current->child[letter] == NULL)
            return false;
        current = current->child[letter];
    }
    return current->isEnd;
}

// Get number of words for prefix ------------------------------------------------------------------------

int Trie::wordsPerPrefix(string prefix)
{
    nodePtr current = head;
    for(unsigned int i=0; i<prefix.length(); i++)
    {
        int letter = (int)prefix[i]-(int)'a';
        if(current->child[letter]==NULL)
            return 0;
        else
            current = current->child[letter];
    }
    return current->prefixCount;
}