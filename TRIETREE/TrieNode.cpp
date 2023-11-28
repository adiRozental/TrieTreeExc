#include "TrieTree.h"

Trie::TrieNode::TrieNode(TrieNode* par, char val)//building a new object
{
    parent = par;
    value = val;
}
//the func gets an array and sort it by using bubble sort
void Trie::TrieNode::BubbleSort(TrieNode* b[], int len)
{
    bool swapped = true;
    while (swapped)
    {
        swapped = false;
        for (int i = 0; i < len - 1; i++)
        {
            if (b[i]->value > b[i + 1]->value)
            {
                TrieNode* t = b[i];
                b[i] = b[i + 1];
                b[i + 1] = t;
                swapped = true;
            }
        }
    }
}

//the func gets a char and check if there is such a child for this Node
int Trie::TrieNode::child(char c)
{
    for (int i = 0; i < numOfChildren; i++)//running on the array of children
    {
        if (children != nullptr && children[i]->value == c)//if exist
            return i;
    }
    return -1;//if we couldnt found
}