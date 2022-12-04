#include <bits/stdc++.h>
#include "SearchEngine.h"
#include "TrieNode.h"
#include "TrieTree.cpp"
#include "SearchEngine.cpp"
#include "WebPage.cpp"

using namespace std;

// struct comp {
//     bool operator()(WebPage A, WebPage B) const {
//         if(A.getPageScore() < B.getPageScore())
//           return A.getPageScore() < B.getPageScore();
//         return A.getHyperlink() < B.getHyperlink();
//     }
// };



int main()
{

    ifstream webgraph("web_graph.csv"), keywords("keywords.csv"), impresssions("impressions.csv");

    if(webgraph.fail() || keywords.fail() || impresssions.fail()){
        cout << "FAILURE";
        exit(1);
    }
    else{
        SearchEngine MyEngine(webgraph,keywords,impresssions);

        MyEngine.PageRankAlgo();
        MyEngine.Menu();
    }
}
    