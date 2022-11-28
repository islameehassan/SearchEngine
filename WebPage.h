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
    float clickThroughRate;
    float pageScore;

public:
    static int index;
    int webPageIndex;
    // Default constructor to initialize the hyperlink
    WebPage(string hyperlink);

    WebPage(const WebPage& W); // copy constructor

    // setters and getters for the attributes
    void setPageRank(float pageRank);
    float getPageRank();

    void updatePageScore();
    float getPageScore();

    void updateOutGoingLinks();
    int getOutGoingLinks();

    // updates and get impressions and clicks for the CTR
    void setImpressions(int impressions);
    void updateImpressions();
    int getImpressions();

    void setClicks(int clicks);
    void updateClicks();
    int getClicks();

};

int WebPage::index = 0;

#endif