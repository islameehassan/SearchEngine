#include "WebPage.h"


WebPage::WebPage(){}
WebPage::WebPage(string hyperlink){
    index++;
    
    webPageIndex = index;
    this->hyperLink = hyperLink;
    this->clicks = 0;
    this->impressions = 0;
    this->outGoingLinks = 0;
    
}

WebPage::WebPage(const WebPage& W){
    this->hyperLink = W.hyperLink;
    this->impressions = W.impressions;
    this->outGoingLinks = W.outGoingLinks;
    this->index = W.index;
    this->pageRank = W.pageRank;
    this->pageScore = W.pageScore;
}

void WebPage::setPageRank(float pageRank){
    this->pageRank = pageRank;
}

float WebPage::getPageRank(){
    return pageRank;
}

void WebPage::setClicks(int clicks){
    this->clicks = clicks;
}

void WebPage::updateClicks(){
    // Score should be instantly updated upon clicking on the web page
    clicks++;
    updatePageScore();
}

int WebPage::getClicks(){
    return clicks;
}

void WebPage::setImpressions(int impressions){
    this->impressions = impressions;
}

void WebPage::updateImpressions(){
    // Score should be instantly updated upon clicking on the web page
    impressions++;
    updatePageScore();
}

int WebPage::getImpressions(){
    return impressions;
}

void WebPage::updateOutGoingLinks(){
    outGoingLinks++;
}

int WebPage::getOutGoingLinks(){
    return outGoingLinks;
}

void WebPage::updatePageScore(){
    clickThroughRate = clicks/(impressions*1.0);
    float term = 1 - (0.1*impressions) / (1 + 0.1*impressions);
    pageScore = 0.4 * pageRank + (term * pageRank + term * clickThroughRate)*0.6;
}

float WebPage::getPageScore(){
    return pageScore;
}

int WebPage:: index = 0;
