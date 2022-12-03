#ifndef TRIENODE_H
#define TRIENODE_H
#include <iostream>
#include <set>
#include <map>
using namespace std;


struct comp {
    bool operator()(WebPage A, WebPage B) const {
        if(A.getPageScore() < B.getPageScore())
          return A.getPageScore() < B.getPageScore();
        return A.getHyperlink() < B.getHyperlink();
    }
};

const int ALPHA_SIZE = 26;

struct TrieNode {
   public:
   set<string,comp> webPagesHyperlinks;
   unordered_map<char, TrieNode> children;
   bool isTerminal; //It is true if node represents end of word.
};

TrieNode createNode(){ //creation of new node {
   TrieNode tNode;
   tNode.isTerminal = false;
   set<string,comp> empty;
   tNode.webPagesHyperlinks = empty;
   return tNode;
}

#endif