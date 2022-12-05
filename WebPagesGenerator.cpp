#include <bits/stdc++.h>
using namespace std;


// Pseudo-Random Numbers Generator
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

// rand function exploiting the generator
int rand(int a, int b) { 
    return a + rng() % (b - a + 1); 
}

int main(){
    ifstream RandomWords;
    ofstream WebGraph,Keywords, Impressions;


    RandomWords.open("Randomwords.txt");
    WebGraph.open("web_graph.csv");
    Impressions.open("impressions.csv");
    Keywords.open("keywords.csv");


    int maxWords = 100;
    int websites = 50;
    vector<string> keywords;

    while(!RandomWords.eof()){
        string line;
        RandomWords >> line;
        keywords.push_back(line);
    }


    for(int i = 1; i <= websites; i++){
        Keywords << "www.test" << i << ".com";
        int n = rand(1,10);

        for(int j = 1; j <= n; j++){
            int index = rand(1,99);
            Keywords << "," << keywords[index];
        }
        Keywords << endl;
    }
    int connections = websites * 2;

    for(int i = 1; i < connections; i++)
    {
        int j = rand(1,websites);
    
        WebGraph << "www.test" << i/2 + 1<< ".com,www.test" << j << ".com";
        WebGraph << endl;
    }

    for(int i = 1; i <= websites; i++)
    {
        int impression = rand(1, 200);
        Impressions << "www.test" << i << ".com," << impression << ",0";
        Impressions << endl;
    }
}