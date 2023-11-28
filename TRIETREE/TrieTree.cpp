#pragma once
#include<string>
#include "TrieTree.h"
#include <iostream>
    Trie::Trie()    //default
    { 
        head = new TrieNode();
        head->numOfChildren = 0;
    }

    //the function gets a tree and a string and inserts the string to the tree
    void Trie::insert(TrieNode* pp, string str)
    {
        if (str.length() == 0)//if ther are no chars
            return;
        int index = pp->child(str[0]);//getting the location of the char in the array of children if it exists
        if (index == -1)//if not
        {
            pp->children[pp->numOfChildren++] = new  Trie::TrieNode(pp, str[0]);//adding it to the array
            index = pp->numOfChildren - 1;//the index of the char in the array
        }
        if (str.size() == 1)//if its the last char of the string
            pp->children[index]->isEndOfWord = true;//then its the end of the word
        str.erase(0, 1);//deleting the first char after we added it
        insert(pp->children[index], str);//sending the rest of the word to be added

    }
    //the func gets a treeNode and a string to delete from it
    bool Trie::remove(TrieNode* pp, string str)
    {
        if (str.size() == 0)//if there no chars left to delete
            return 1;
        if (!search(pp, str))//if it doesnt exist in this tree
            return 0;
        int index;
        for (int i = 0; i < str.length(); i++)//getting the location of the last char
        {
            index = pp->child(str[i]);
            pp = pp->children[index];
        }
        if (pp->numOfChildren > 0)//if it has childrens
            pp->isEndOfWord = 0;//so it wont be concidered as a word
        else
        {
            pp->isEndOfWord = 0;
            pp = pp->parent;
            for (int i = str.length() - 1; i >= 0; i--)//running on the string
            {
                if (pp != nullptr)
                {
                    index = pp->child(str[i]);//finding th4e char index in the array
                    if (pp->children[index]->numOfChildren > 0)//if its child has childs too we cant delete the char
                        return 1;
                    if (pp->numOfChildren == 1)//if not (ecxept for the rest of the string that we delete)
                        delete pp->children[--pp->numOfChildren];//deleting the current char
                    else
                    {
                        pp->children[index] = pp->children[--pp->numOfChildren];//replacing it
                    }
                    if (pp->isEndOfWord)//if theres an interna word
                        return 1;
                    pp = pp->parent;//after deleting the current, going to the parent in order to delete the previous char
                }
            }
        }
        return 1;

    }

    //the func gets a syring and checks if it exists in the tree
    bool Trie::search(TrieNode* pp, string str)
    {
        int index = pp->child(str[0]);//getting the first char index
        if (index == -1)//if it doesnt exists
            return 0;//false- there isnt such a word
        if (str.length() == 1 && pp->children[index]->isEndOfWord)//if length 1 and its the end of the word then the word was found
            return true;
        str.erase(0, 1);//deeting the first char 
        return search(pp->children[index], str);//sendind the rest of the word to be serched in the tree
    }

    //the function gets a tree and a string and prints all the possible options to complete this word
    bool Trie::print(TrieNode* pp, string p)
    {
        int index;
        for (int i = 0; i < p.length(); i++)//getting the last char location 
        {
            index = pp->child(p[i]);
            if (index == -1)//if doesnt exists
                return 0;
            pp = pp->children[index];
        }
        if (pp->isEndOfWord)//if its a word, printing it
            cout << p << endl;
        DOprint(p, pp);//sending to the func to print all the tree of the last char that we found
        return 1;
    }

    //the function gets a tree and a string and prints the string + whole words on this trre (every completion by itself)
    void Trie::DOprint(string p, TrieNode* pp)
    {
        pp->BubbleSort(pp->children, pp->numOfChildren);//sorting the array
        string str;
        for (int i = 0; i < pp->numOfChildren; i++)//Running on the array
        {
            str = p + pp->children[i]->value;//adding the current char to the prefix
            if (pp->children[i]->isEndOfWord)//if its end of a word, print it
                cout << str << endl;
            DOprint(str, pp->children[i]);//going to the current char childrens to add them as well 
        }
    }


