#ifndef SEARCH_ENGINE_H
#define SEARCH_ENGINE_H
#include <iostream>
#include <sstream>
#include <fstream>
#include <set>
#include <vector>
#include <unordered_map>
#include <cmath>

#include "WebPage.h"
#include "TrieTree.h"
using namespace std;


// CONSTANTS
#define ERROR 0.001 // A threshold that is set to mark the end of the page rank algorithms's iterations
#define DAMPING 0.15 // A constant factor included in the page rank algorithm to avoid the disastrous effect of
                     // dangling nodes, or nodes that have no outgoing edges



class SearchEngine{
    // Number of web pages registered on the engine
    int noWebPages;

    // Adjacency Matrix showing the connections between the different websites, and is also used for 
    // calculations related to the page rank algorithm
    vector<vector<float>> WebGraph;
    
    // Vector storing the page rank scores of the websites
    vector<float> PageRank;

    // A trie tree storing all keywords
    Trie Keywords;
    
    // Unordered map used to map each website's hyperlink to the WebPage objects
    unordered_map <string,WebPage> WebPages;

    // Different types of queries 
    vector<string> ANDQuery(set<string> KeyWords);
    vector<string> ORQuery(set<string> KeyWords);
    vector<string> QuotationQuery(string keyword);

    // Vector to store the latest search hyperlinks
    vector<string> SearchResults;

    // calculate the euclidean norm to be compared to the ERROR
    float norm(vector<float>& PrevRank, vector<float>& CurrRank);
    
    // display the web pages according to the search query
    void displayResults(vector<string> results);

    // init the web graph, trie tree, and web pages' impressions and clicks scores
    void initWebGraph(ifstream& initWebGraph);
    void initKeywords(ifstream& Keywords);
    void initImpressionsandClicks(ifstream& Impressions);
public:
    // Default Constructor
    SearchEngine(ifstream &WebGraph,ifstream &KeyWords,ifstream &Impressions);

    // run the page rank algorithm to get the scores
    void PageRankAlgo();

    void Menu();

    // run a query 
    void Search(string searchQuery);

    // update web page's attributes as per user's choice
    void Update(int choice);

    void RunEngine();

    ~SearchEngine();
};

#endif