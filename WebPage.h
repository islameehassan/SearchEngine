#ifndef Web_Page_H
#define Web_Page_H
#include <iostream>
#include <set>
#include <vector>
#include <map>
using namespace std;

class WebPage
{
    // attributes of the webpage
    string hyperLink;
    int clicks;
    int impressions;
    int outGoingLinks;
    float pageRank;
    float pageScore;

    set<string> keyWords;

    static int index;
public:
    // Paramterized constructor to initialize all attributes of the webpage
    WebPage(string hyperLink, int impressions, set<string>& keyWords, int click = 0, int outGoingLink = 0);

    // setters and getters for the attributes
    void setPageRank(float pageRank);
    float getPageRank();

    void setpageScore();
    float getPageScore();

    void setOutGoingLinks(int outGoingLinks);
    int getOutGoingLinks();

    // updates and get impressions and clicks for the CTR
    void updatedImpressions();
    int getImpressions();

    void updatedClicks();
    int getClicks();

    set<string> getKeyWords();
};

#endif