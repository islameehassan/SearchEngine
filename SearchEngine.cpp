#include "SearchEngine.h"

SearchEngine::SearchEngine(ifstream &WebGraphFile,ifstream &KeywordsFile,ifstream &ImpressionsFile){
    Keywords = Trie(); // init the trie tree

    // Get the keywords from the Keywords file
    string line;
    getline(KeywordsFile,line);


    while(line != ""){
        stringstream s(line);

        // get the hyperlink of the webpage
        string hyperlink;
        getline(s,hyperlink,',');
        // map each web page object to its hyperlink through the WebPages Map
        // insert the keyword along with the hyperlink of the web page in the trie tree
        string keyWord;
        WebPages[hyperlink] = WebPage(hyperlink);
        while(getline(s,keyWord, ',') || getline(s,keyWord, '\n')){
            Keywords.insertWord(keyWord, hyperlink);
        }

        getline(KeywordsFile,line);
    }
    KeywordsFile.close();


    // Get # of impressions from the impressions file
    line = "";
    getline(ImpressionsFile,line);
    int noOfWebPages = 0; // no of web pages is the number of lines in this file
    while(line != ""){
         noOfWebPages++;

        stringstream s(line);

        // get the hyperlink of the webpage
        string hyperlink;
        getline(s,hyperlink,',');

        // get the number of impressions and clicks
        int noImpressions, noClicks;
        string temp;

        getline(s,temp,',');
        noImpressions = stoi(temp);

        getline(s,temp);
        noClicks = stoi(temp);

        // set the web page's number of clicks and impressions
        WebPages[hyperlink].setImpressions(noImpressions);
        WebPages[hyperlink].setClicks(noClicks);

        getline(ImpressionsFile, line);
    }
    ImpressionsFile.close();

    // Build the web graph 
    line = "";

    // resize the web graph matrix
    this->noWebPages = noOfWebPages;
    WebGraph.resize(noOfWebPages+1);
    for(vector<float>& v: WebGraph)
        v.resize(noOfWebPages+1);
    
    int index = 0;
    getline(WebGraphFile,line);
    while(line != ""){
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
        
        // mark that there is an edge from web page 1 to web page 2, equal to 1 - DAMPING FACTOR
        WebGraph[indexInWebGraph2][indexInWebGraph1] = 1 - DAMPING;
        getline(WebGraphFile,line);

    }
    WebGraphFile.close();

    PageRank.resize(noOfWebPages);
}

void SearchEngine::PageRankAlgo(){
    // Store the ranks of pages in he current and previous iteration for comparison purposes
    vector<float> CurrPageRank(noWebPages+1, 1.0/noWebPages);
    vector<float> PrevPageRank(noWebPages+1,1.0/noWebPages);

    int i = 1;
    for(auto& p: WebPages){
        int links = p.second.getOutGoingLinks();
        int index = p.second.webPageIndex;
        for(int j = 1; j <= noWebPages; j++){
            WebGraph[j][index] *= 1.0/links;
        }
    }


    float scoreNorm;
    vector<float> ScoreDiff;

    // Do the iterations 
    do{
        for(int i = 1; i <=noWebPages; i++)
            PrevPageRank[i] = CurrPageRank[i];
        for(int i = 1; i <= noWebPages; i++){
            float score = 0;
            for(int j = 1; j <= noWebPages; j++){
                score = score + (WebGraph[i][j] * PrevPageRank[j]);
            }
            CurrPageRank[i] = score + (1.0/noWebPages * DAMPING); // adding the damping factor 
        }

        // calculate the euclidean norm by summing the square of the score difference and then take the square root
        scoreNorm = norm(PrevPageRank, CurrPageRank);

    }while(scoreNorm>ERROR); // keep iterating as long as the norm is greater than the error


    // Update the PageRank vector
    for(int i = 1; i <= CurrPageRank.size(); i++){
        PageRank[i] = CurrPageRank[i];
    }

    i = 1;
    for(auto& p: WebPages){
        p.second.setPageRank(PageRank[i++]);
    }
    
}

float SearchEngine::norm(vector<float>& PrevRank, vector<float>& CurrRank){
    float euclideanNorm = 0;

    for(int i = 1; i <= CurrRank.size(); i++){
        euclideanNorm += pow(abs(CurrRank[i] - PrevRank[i]), 2);
    }    

    return sqrtf(euclideanNorm);
}

void SearchEngine::Search(string searchQuery){
    
    vector<string> results;

    // Search Query with quotations
    if(searchQuery[0] == '\"'){

        // find the first occurence of a letter to avoid redundant spaces before the word
        // by the user
        int firstOccurence = 0;
        for(int i = 0; i < searchQuery.size(); i++){
            if(searchQuery[i] != ' ' || searchQuery[i] != '\"'){
                firstOccurence = i;
                break;
            }
        }
        // extract the keyword starting from the first letter till the end, excluding the last quotation mark
        results = QuotationQuery(searchQuery.substr(firstOccurence, searchQuery.size() - firstOccurence- 1));

        // Display results, if any
        displayResults(results);
    }
    else{

        int andIndex = searchQuery.find("AND", 0); // if the query has AND keyword
    
        stringstream s(searchQuery);
        set<string> tempKeywords;

        // extract the keywords from the search query string
        string keyword;
        while(getline(s,keyword, ' ')){
            tempKeywords.insert(keyword);

            getline(s, keyword, ' '); // ignore the AND
        }
        
        if(andIndex != -1) // Search Query with AND
            results = ANDQuery(tempKeywords);
        else // Search Query containing OR or plain
            results = ORQuery(tempKeywords);

        // display results
        displayResults(results);
    }
    SearchResults = results;

}


void SearchEngine::displayResults(vector<string> results){

    if(results.size() == 0)
        cout << "No Web Page found that matches your search\n";
    else{
        int index = 0;
        for(string result:results){
            cout << ++index << ". " << result << '\n';
            WebPages[result].updateImpressions();
        }
    }
}


vector<string>SearchEngine::ANDQuery(set<string> _Keywords){
    vector<string> results;

    for(string keyword: _Keywords){
        set<string> temp = Keywords.search(keyword); // extracting the web pages from the trie tree

        // erasing web pages that do not contain the current keyword
        for(auto it = results.begin(); it != results.end(); it++){
            if(temp.find(*it) == temp.end()){
                results.erase(it);
            }
        }

        int index = 0;
        if(results.size() == 0){
            for(string t: temp)
                results[index] = t;
        }
    }

    return results;

}

vector<string> SearchEngine::ORQuery(set<string> _Keywords){
    set<string> temp;

    set<WebPage,comp> results;


    for(string keyword: _Keywords){
        // inserting all web pages associated with the keyword
        set<string> temp = this->Keywords.search(keyword);
        for(string t: temp)
            results.insert(WebPages[t]);
        
    }
    vector<string> result;
    int index = 0;
    for(WebPage A:results)
        result.push_back(A.getHyperlink());


    return result;
}

vector<string> SearchEngine::QuotationQuery(string keyword){
    vector<string> result;

    set<WebPage,comp> results;

    // inserting all web pages associated with the keyword
    set<string> temp = this->Keywords.search(keyword);
    for(string t: temp)
        results.insert(WebPages[t]);
    
    for(WebPage A: results)
        result.push_back(A.getHyperlink());
    
    return result;
}

void SearchEngine:: Update(int choice){
    string hyperlink = SearchResults[choice - 1];

    WebPages[hyperlink].updateClicks();
}
void SearchEngine:: Menu()
{
    cout << "Welcome!\n"; 
    reset_label:
    cout << "What would you like to do?\n"; 
    int choice; 
    cout << "1. New search\n"; 
    cout << "2. Exit\n"; 
    cout << "\nType in your choice: "; 
    cin >> choice;
    while(true)
    {
        /* int choice; 
        cout << "1. New search\n"; 
        cout << "2. Exit\n"; 
        cout << "\nType in your choice: "; 
        cin >> choice;  */
        if(choice == 2)
        {
            break;
        }
        else if(choice == 1)
        {
            newsearch_label:
            int choice2;
            string query;
            cout << "Enter your search: ";
            cin >> query; 
            cout << "\nSearch Results:\n";

            Search(query);

            if(SearchResults.size() != 0)
            {
                results_label:
                cout << "\nWould you like to\n";
                cout << "1. Choose a webpage to open\n"; 
                cout << "2. New search\n"; 
                cout << "3. Exit\n"; 
                cout << "\nType in your choice: ";
                cin >> choice2;

                if(choice2 == 3)
                {
                    goto final_label;
                }
                else if(choice2 == 2)
                {
                    goto newsearch_label;
                }
                else if(choice2 == 1)
                {
                    int webpage_choice;
                    cout << "Which webpage you want to disply? ";
                    cin >> webpage_choice;
                    while (webpage_choice > SearchResults.size() || webpage_choice < 1)
                    {
                        cout << "Please enter a valid choice: ";
                        cin >> webpage_choice;
                    }
                    cout << "You are currently viewing " << SearchResults[webpage_choice-1] << endl;
                    Update(webpage_choice);

                    int choice3;
                    cout << "Would you like to\n";
                    cout << "1. Back to search results\n"; 
                    cout << "2. New search\n"; 
                    cout << "3. Exit\n"; 
                    cout << "\nType in your choice: ";
                    cin >> choice3;
                    while(choice3 > 3 || choice3 < 1)
                    {
                        cout << "Please enter a valid choice: ";
                        cin >> choice3;
                    }
                    if (choice3 == 1)
                    {
                        int index = 0;
                        for(string result:SearchResults)
                        {
                            cout << ++index << ". " << result << '\n';
                        }
                        goto results_label;
                    }
                    else if(choice3 == 2)
                    {
                        goto newsearch_label;
                    }
                    else
                    {
                        goto final_label;
                    }
                }
            }
            else
            {
                goto reset_label;
            }
        }
        else
        {
            cout << "Enter a valid choice "; 
        }
    }
    final_label:
    return;
}

SearchEngine::~SearchEngine(){
    ofstream ImpressionsFile;
    ofstream PageScores;

    ImpressionsFile.open("impressions.csv");
    PageScores.open("PageScore.csv");

    for(auto it = WebPages.begin(); it != WebPages.end(); it++){
        ImpressionsFile << it->first << "," << it->second.getImpressions() << "," << it->second.getClicks() << '\n';
        PageScores << it->first << "," << it->second.getPageScore() << "," << it->second.getPageRank() << '\n';
    }
}