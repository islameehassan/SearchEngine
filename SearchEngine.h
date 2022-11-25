#ifndef SEARCH_ENGINE_H
#define SEARCH_ENGINE_H
#include <iostream>
#include <fstream>
#include <set>
#include <vector>
#include <map>

#include "WebPage.h"
#include "TrieTree.h"
using namespace std;


auto comp = [](WebPage A, WebPage B) {return A.getPageScore() > B.getPageScore();};

class SearchEngine{
    vector<vector<int>> WebGraph; // the web graph constructed to calculate the web pages rank
    vector<float> PageRank;
    Trie Keywords; // a trie tree containing all keywords
    map <string,WebPage> WebPages; // associate each webpage to a key, that is its hyperblink

    set<string> ANDQuery(set<string> KeyWords);
    set<string> ORQuery(set<string> KeyWords);
    set<string> QuotationQuery(string keyword);
public:
    // JumpStart the engine by feeding in all input files to initialize the web Graph and the keywords Trie Tree
    SearchEngine(fstream WebGraph,fstream KeyWords,fstream Impressions);

    void Menu(); // Menu displayed for the user, where console is cleared every time the user chooses.

    void PageRankAlgo(); // run the page rank algorithm to get page rank scores for all webpages

    void updatePagesScore(); // update scores 

    void Search(string searchQuery); // run a search using a search query from the user

    void RunEngine();
};



#endif