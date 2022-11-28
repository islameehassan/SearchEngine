#include "SearchEngine.h"

SearchEngine::SearchEngine(fstream WebGraphFile,fstream KeywordsFile,fstream ImpressionsFile){
    Keywords = Trie(); // init the trie tree

    // Get the keywords from the Keywords file
    freopen("KeyWords.csv", "r", stdin);
    string line;

    while(!KeywordsFile.eof()){
        getline(cin,line);
        stringstream s(line);

        // get the hyperlink of the webpage
        string hyperlink;
        getline(s,hyperlink,',');

        // map each web page object to its hyperlink through the WebPages Map
        // insert the keyword along with the hyperlink of the web page in the trie tree
        string keyWord;
        while(getline(s,keyWord, ',') || getline(s,keyWord, '\n')){
            WebPages[hyperlink] = WebPage(hyperlink);
            Keywords.insertWord(keyWord, hyperlink);
        }
    }
    KeywordsFile.close();


    // Get # of impressions from the impressions file
    freopen("Impressions.csv", "r", stdin);
    line = "";
    int noOfWebPages; // no of web pages is the number of lines in this file
     while(!ImpressionsFile.eof()){
        noOfWebPages++;

        getline(cin,line);
        stringstream s(line);

        // get the hyperlink of the webpage
        string hyperlink;
        getline(s,hyperlink,',');

        // get the number of impressions and clicks
        int noImpressions, noClicks;
        string temp;

        getline(s,temp,',');
        noImpressions = stoi(temp);

        getline(s,temp,'\n');
        noClicks = stoi(temp);

        // set the web page's number of clicks and impressions
        WebPages[hyperlink].setImpressions(noImpressions);
        WebPages[hyperlink].setClicks(noClicks);
    }
    ImpressionsFile.close();

    // Build the web graph 
    freopen("WebGraph.csv","r",stdin);
    line = "";

    // resize the web graph matrix
    this->noWebPages = noOfWebPages;
    WebGraph.resize(noOfWebPages+1);
    for(vector<float> v: WebGraph)
        v.resize(noOfWebPages+1);
    
    int index = 0;
     while(!WebGraphFile.eof()){
        getline(cin,line);
        stringstream s(line);

        // get the hyperlink of the first web page
        string hyperlink1;
        getline(s,hyperlink1,',');

        WebPages[hyperlink1].updateOutGoingLinks(); // increase the outgoing links of the first web page by one

        // get the hyperlink of the second web page
        string hyperlink2;
        getline(s,hyperlink2,'\n');
        
        // get the indices of the web pages in the Web Graph
        int indexInWebGraph1 = WebPages[hyperlink1].webPageIndex;
        int indexInWebGraph2 = WebPages[hyperlink2].webPageIndex;
        
        // mark that there is an edge from web page 1 to web page 2
        WebGraph[indexInWebGraph1][indexInWebGraph2] = 1;
    }
    WebGraphFile.close();
}

void SearchEngine::PageRankAlgo(){
    // Store the ranks of pages in he current and previous iteration for comparison purposes
    vector<float> CurrPageRank(noWebPages+1);
    vector<float> PrevPageRank(noWebPages+1,1);

    // Store the pages' outgoing links no
    vector<int> outGoingLinks(noWebPages+1);
    int i = 0;
    for(auto p: WebPages)
        outGoingLinks[i] = p.second.getOutGoingLinks();


    float scoreNorm;
    vector<float> ScoreDiff;

    // Do the iterations 
    do{

        for(int i = 1; i <= noWebPages; i++){
            float score = 0;
            for(int j = 1; j <= noWebPages; j++){
                score = score + (WebGraph[j][i] * PrevPageRank[j]);
            }
            CurrPageRank[i] = score;
        }

        scoreNorm = norm(PrevPageRank, CurrPageRank);

    }while(scoreNorm>ERROR);

    for(int i = 1; i <= CurrPageRank.size(); i++){
        PageRank[i] = CurrPageRank[i];
    }
    
}

float SearchEngine::norm(vector<float>& PrevRank, vector<float>& CurrRank){
    float euclideanNorm;

    for(int i = 1; i <= CurrRank.size(); i++){
        euclideanNorm = pow(abs(CurrRank[i] - PrevRank[i]), 2);
    }    

    return sqrtf(euclideanNorm);
}