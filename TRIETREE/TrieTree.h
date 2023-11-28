#pragma once
#include<string>
#include<cstring>
using namespace std;
class Trie
{
    class TrieNode
    {
    public:
        TrieNode** children = new TrieNode * [26];//= new TrieNode();
        TrieNode* parent;
        // isEndOfWord is true if the node
        // represents end of a word
        bool isEndOfWord = false;
        int numOfChildren = 0;
        char value;
        TrieNode() {  }
        TrieNode(TrieNode* par, char val);
        void BubbleSort(TrieNode* b[], int len); 
        int child(char c);
    };


public:
    TrieNode* head = nullptr;
    Trie();//default
    void insert(TrieNode* pp, string str);
    bool remove(TrieNode* pp, string str);
    bool search(TrieNode* pp, string str);
    bool print(TrieNode* pp, string p);
    void DOprint(string p, TrieNode* pp);

};

