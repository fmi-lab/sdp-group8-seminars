#include "FeedExplorer.h"
#include <string>
#include "FeedArticle.hpp"
#include <sstream>
#include <fstream>
#include <iostream>
FeedExplorer::FeedExplorer(std::string rssFeed)
    :filename(rssFeed),lastPos(0), isRead(false), isDone(false)
{ }

FeedExplorer::operator bool() const{
    return !isDone;
}

FeedExplorer& FeedExplorer::operator>>(FeedArticle& article) {
    if (isDone) {
        // nothing more to do
        return *this;
    }
    if (!isRead) {
        std::ifstream t(filename.c_str());
        std::stringstream buffer;
        buffer << t.rdbuf();
        allData = buffer.str();
        isRead = true;
    }
    unsigned int nextEntryPos = allData.find("<entry>", lastPos);
    if (nextEntryPos == std::string::npos) {
        // end of data reached
        isDone = true;
    } else {
        int urlIdxStart = allData.find("<id>",nextEntryPos);
        int urlIdxEnd = allData.find("</id>", urlIdxStart);
        int titleIdxStart = allData.find("<title type=\"text\">", nextEntryPos);
        int titleIdxEnd = allData.find("</title>", titleIdxStart);

        article.url = allData.substr(urlIdxStart + 4, urlIdxEnd - urlIdxStart - 4);
        article.title = allData.substr(titleIdxStart + 19, titleIdxEnd - titleIdxStart - 19);
        lastPos = allData.find("</entry>", nextEntryPos);
    }
    return *this;
}
