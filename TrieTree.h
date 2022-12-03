#ifndef TRIE_TREE_H
#define TRIE_TREE_H
#include "TrieNode.h"
using namespace std;





#define ALPHAPET 26



class Trie{
    TrieNode root;
    TrieNode* _insert(string word); // insert a new word in the trie
    TrieNode* _search(string word); // search for a given word if it exists in the tree
    bool isEmpty(TrieNode* root); // check if a given node has no children
    TrieNode* deleteAll(TrieNode* root); // delete the entire tree to free up memory

public:
    Trie(); // initialize the tree

    void insertWord(string word, string webPageHyperlink); // insert a word in the tree along with
                                                           // the page's hyperlink this keyword is found in
    
    set<string,comp> search(string word); // return the list of webpages associated with a keyword, it exists

    ~Trie();
};



#endif