#include <bits/stdc++.h>
#include "SearchEngine.h"
#include "TrieNode.h"
#include "TrieTree.cpp"
#include "SearchEngine.cpp"
#include "WebPage.cpp"

using namespace std;



int main(){
    ifstream webgraph("web_graph.csv"), keywords("keywords.csv"), impresssions("impressions.csv");

    if(webgraph.fail() || keywords.fail() || impresssions.fail()){
        cout << "FAILURE";
        exit(1);
    }
    else{
    

    SearchEngine MyEngine(webgraph,keywords,impresssions);

    MyEngine.PageRankAlgo();
    MyEngine.Search("objects OR python OR learning");

    // Trie trie = MyEngine.Keywords;


    // set<string> s = trie.search("data");
    // cout << *s.begin();
    }

}
    