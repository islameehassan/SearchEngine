#include "TrieTree.h"

Trie::Trie(){
    root = createNode();
}

TrieNode* Trie::_insert(string word){
    TrieNode* nCrawl = &root;

    for(int i = 0; i < word.size();i++){
        char index = word[i];

        if(nCrawl == NULL)
            cout << "YES\n";

        if(word[i] == ' ')
            continue;
        // create a node for a char in the word if not created yet
        if(nCrawl->children.find(index) == nCrawl->children.end()){
            nCrawl->children[index] = createNode();
        }

        
        // traverse
        nCrawl = &nCrawl->children[index];
    }
    nCrawl->isTerminal = true;

    return nCrawl;
}

void Trie::insertWord(string word, string webPageHyperlink){
    TrieNode* node = _insert(word);
    

    node->webPagesHyperlinks.insert(webPageHyperlink);
}

TrieNode* Trie::_search(string word){
   TrieNode* nCrawl = &root;

   for(int i = 0; i < word.size();i++){
        char index = word[i];

        if(word[i] == ' ')
            continue;
        
        if(nCrawl->children.find(index) == nCrawl->children.end())
            return NULL;
        
        nCrawl = &nCrawl->children[index];
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
        if(root->children[i].isTerminal)
            return false;
    }
    return true;
}

TrieNode* Trie::deleteAll(TrieNode* root){
    if(root == NULL)
        return NULL;
    
    for(int i = 0; i < ALPHAPET;i++){
        if(root->children[i].isTerminal){
            deleteAll(&root->children[i]);
        }
    }

    root = NULL;
    return root;
}

Trie::~Trie(){
    TrieNode* deletedTrie = deleteAll(&root);
    if(deletedTrie != NULL){
        cout << "Error occured while deleting the trie tree\n";
        exit(1); // safe exit from the program
    }
}