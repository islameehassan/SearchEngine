#ifndef TRIENODE_H
#define TRIENODE_H
#include <iostream>
#include <set>
#include <map>
using namespace std;

const int ALPHA_SIZE = 26;

struct TrieNode {
   public:
   set<string> webPagesHyperlinks;
   unordered_map<char, TrieNode> children;
   bool isTerminal; //It is true if node represents end of word.
};

TrieNode createNode(){ //creation of new node {
   TrieNode tNode;
   tNode.isTerminal = false;
   set<string> empty;
   tNode.webPagesHyperlinks = empty;
   cout << tNode.webPagesHyperlinks.size();
   return tNode;
}

#endif