#ifndef SEARCH_ENGINE_H
#define SEARCH_ENGINE_H
#include <iostream>
#include <set>
#include <vector>
#include <map>

#include "WebPage.h"
#include "TrieTree.h"
using namespace std;


auto comp = [](WebPage A, WebPage B) {return A.getPageScore() > B.getPageScore();};

class SearchEngine{
    vector<vector<int>> WebGraph; // the web graph constructed to calculate the web pages rank
    map <string,WebPage> webPages; // associate each webpage to a key, that is its hyperblink




};



#endif