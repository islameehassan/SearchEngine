#include "TrieTree.h"

Trie::Trie(){
    root = createNode();
}

Node* Trie::insert(string word){

    // create the pointer that will traverse the tree, which is initially pointing to the
    // the root
    Node* nCrawl = &root;

    for(int i = 0; i < word.size();i++){
        char index = word[i];

        // Skip the space character
        if(word[i] == ' ')
            continue;
        

        // create a node for a char in the word if not created yet
        if(nCrawl->Children.find(index) == nCrawl->Children.end()){
            nCrawl->Children[index] = createNode();
        }

        
        // traverse
        nCrawl = &nCrawl->Children[index];
    }
    // mark the last word's bool as true to know that we have reached the end of a keyword
    nCrawl->isTerminal = true;

    return nCrawl;
}

void Trie::insertKey(string word, string hyperlink){
    Node* node = insert(word);

    // add the hyperlink associated with the word inserted in the tree
    node->Hyperlinks.insert(hyperlink);
}

Node* Trie::search(string word){
   Node* nCrawl = &root;

   for(int i = 0; i < word.size();i++){
        char index = word[i];

        if(word[i] == ' ')
            continue;
        
        if(nCrawl->Children.find(index) == nCrawl->Children.end())
            return NULL;
        
        nCrawl = &nCrawl->Children[index];
   }

   // if the last character's bool is true, then we have found a word
   if(nCrawl->isTerminal)
        return nCrawl;
    return NULL;
}

set<string> Trie::searchword(string word){
    set<string> Hyperlinks;

    Node* node = search(word);

    // node is NULL, and thus no hyperlinks have been found
    if(node == NULL)
        return Hyperlinks;
    
    return node->Hyperlinks;
}

bool isEmpty(Node* root){
    if(root == NULL)
        return false;
    
    for(int i = 0; i < ALPHAPET;i++){
        if(root->Children[i].isTerminal)
            return false;
    }
    return true;
}

Node* Trie::deleteTree(Node* root){
    if(root == NULL)
        return NULL;
    
    for(int i = 0; i < ALPHAPET;i++){
        if(root->Children[i].isTerminal){
            deleteTree(&root->Children[i]);
        }
    }

    root = NULL;
    return root;
}

Trie::~Trie(){
    Node* deletedTrie = deleteTree(&root);
    if(deletedTrie != NULL){
        cout << "Error occured while deleting the trie tree\n";
        exit(1); // safe exit from the program
    }
}