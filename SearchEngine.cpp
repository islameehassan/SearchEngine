#include "SearchEngine.h"

SearchEngine::SearchEngine(fstream WebGraphFile,fstream KeywordsFile,fstream ImpressionsFile){
    Keywords = Trie(); // init the trie tree

    // Get the keywords from the Keywords file
    freopen("KeyWords.csv", "r", stdin);
    string line;

    while(!WebGraphFile.eof()){
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


    // Get No of impressions from the impressions file
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
    for(vector<int> v: WebGraph)
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

        if(HyperLinkToIndex.find(hyperlink1) == HyperLinkToIndex.end())
            HyperLinkToIndex[hyperlink1] = index++;
        
        if(HyperLinkToIndex.find(hyperlink2) == HyperLinkToIndex.end())
            HyperLinkToIndex[hyperlink2] = index++;
        
        // get the indices of the web pages in the Web Graph
        int indexInWebGraph1 = HyperLinkToIndex[hyperlink1];
        int indexInWebGraph2 = HyperLinkToIndex[hyperlink2];
        
        // mark that there is an edge from web page 1 to web page 2
        // WebGrapg[i][j] means there is an edge from j to it
        // Graph is defined this way for the sake of the page rank algorithm
        WebGraph[indexInWebGraph2][indexInWebGraph1] = 1;
    }
    WebGraphFile.close();
}