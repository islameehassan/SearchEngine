#include <bits/stdc++.h>
#include "SearchEngine.h"
#include "TrieNode.h"
using namespace std;

auto comp = [](WebPage A, WebPage B) {return A.getPageScore() > B.getPageScore();};



int main(){
    ifstream webgraph("web_graph.csv"), keywords("keywords.csv"), impresssions("impressions.csv");

    if(webgraph.fail() || keywords.fail() || impresssions.fail()){
        cout << "FAILURE";
        exit(1);
    }
    else
        cout << "SUCCESSS\n";
    

    SearchEngine MyEngine(webgraph,keywords,impresssions);

    Trie trie = MyEngine.Keywords;


    set<string> s = trie.search("data");
    cout << *s.begin();
}
    