#include "TrieTree.h"

Trie::Trie(){
    this->root = createNode();
}

TrieNode* Trie::createNode(){
    TrieNode* node = new TrieNode;

    node->isTerminal = false;

    for(int i = 0; i < ALPHAPET; i++)
        node->children[i] = NULL;
    
    return node;
}

TrieNode* Trie::_insert(string word){
    TrieNode* nCrawl = this->root;

    for(int i = 0; i < word.size();i++){
        int index = word[i] - 'a';

        if(word[i] == ' ')
            index = 26;

        // create a node for a char in the word if not created yet
        if(nCrawl->children[index] == NULL)
            nCrawl->children[index] = createNode();
        
        // traverse
        nCrawl = nCrawl->children[index];
    } 
    nCrawl->isTerminal = true;

    return nCrawl;
}

void Trie::insertWord(string word, string webPageHyperlink){
    TrieNode* node = _insert(word);
    
    node->webPagesHyperlinks.insert(webPageHyperlink);
}

TrieNode* Trie::_search(string word){
   TrieNode* nCrawl = this->root;

   for(int i = 0; i < word.size();i++){
        int index = word[i] - 'a';

        if(word[i] == ' ')
            index = 26;
        if(nCrawl->children[index] == NULL)
            return NULL;
        
        nCrawl = nCrawl->children[index];
   }

   if(nCrawl->isTerminal)
        return nCrawl;
    return NULL;
}

set<string> Trie::search(string word){
    set<string> webPagesHyperlinks;

    TrieNode* node = _search(word);
    if(node == NULL)
        return webPagesHyperlinks;
    
    return node->webPagesHyperlinks;
}

bool isEmpty(TrieNode* root){
    if(root == NULL)
        return false;
    
    for(int i = 0; i < ALPHAPET;i++){
        if(root->children[i] != NULL)
            return false;
    }
    return true;
}

TrieNode* Trie::deleteAll(TrieNode* root){
    if(root == NULL)
        return NULL;
    
    for(int i = 0; i < ALPHAPET;i++){
        if(root->children[i] != NULL){
            deleteAll(root->children[i]);
        }
    }

    delete root;
    root = NULL;
    return root;
}

Trie::~Trie(){
    TrieNode* deletedTrie = deleteAll(this->root);
    if(deletedTrie != NULL){
        cout << "Error occured while deleting the trie tree\n";
        exit(1); // safe exit from the program
    }
}