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


    static int index;
public:
    // Default constructor to initialize the hyperlink
    WebPage(string hyperlink);

    // setters and getters for the attributes
    void setPageRank(float pageRank);
    float getPageRank();

    void updatePageScore();
    float getPageScore();

    void setOutGoingLinks(int outGoingLinks);
    int getOutGoingLinks();

    // updates and get impressions and clicks for the CTR
    void setImpressions(int impressions);
    void updateImpressions();
    int getImpressions();

    void setClicks(int clicks);
    void updateClicks();
    int getClicks();

};

#endif