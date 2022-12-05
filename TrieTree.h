#ifndef TRIE_TREE_H
#define TRIE_TREE_H
#include "Node.h"
using namespace std;

/*
A trie tree is often called a prefix tree. Nodes of the tree consist of an unordered map
pointing to the next 26 possible characters in the English language. 

Operations Complexity:
Search: O(log l) --> l is the length of the keywrod
Insertion: O(log l) ---> We can assume it is O(1) since l is not theoretically that large
Delete: O(log l)
*/



class Trie{
    // Root of the trie tree
    Node root;

    // insert a string word in the tree
    Node* insert(string word);
    
    // search for a given word in the tree in O(log l), where l is the length of the keyword
    Node* search(string word); 

    // check if the current node has children or not
    bool isEmpty(Node* root);

    // delete the entire tree allocated on the heap to free up memory
    Node* deleteTree(Node* root); 

public:
    // Default Constructor
    Trie();

    // insert a word in the tree along with
    // the page's hyperlink this keyword is found in
    void insertKey(string word, string hyperlink);

    // return the list of webpages associated with a keyword, it exists
    set<string> searchword(string word);

    // Desctructor calling the private method deleteTree
    ~Trie();
};



#endif