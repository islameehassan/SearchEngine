#ifndef TRIENODE_H
#define TRIENODE_H
#include <iostream>
#include <set>
using namespace std;

#define ALPHAPET 27

struct TrieNode{
    TrieNode* children[ALPHAPET];
    set<string> webPagesHyperlinks = {};
    bool isTerminal; // end of word flag
};

#endif