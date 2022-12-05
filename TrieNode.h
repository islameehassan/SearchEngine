#ifndef Node_H
#define Node_H
#include <iostream>
#include <set>
#include <map>
#include <unordered_map>
#include "WebPage.h"
using namespace std;


struct comp {
    bool operator()(WebPage A, WebPage B) const {
        if(A.getPageScore() != B.getPageScore())
          return A.getPageScore() > B.getPageScore();
        return A.getHyperlink() < B.getHyperlink();
    }
};

const int ALPHA_SIZE = 26;

struct Node {
   public:
   set<string> webPagesHyperlinks; // web pages associated with the word inserted
   unordered_map<char, Node> children; // each char has 26 subsequent characters
   bool isTerminal; //flags the end of the word if true
};

Node createNode(){ //creation of new node
   Node tNode;
   tNode.isTerminal = false;
   set<string> empty;
   tNode.webPagesHyperlinks = empty;
   return tNode;
}

#endif