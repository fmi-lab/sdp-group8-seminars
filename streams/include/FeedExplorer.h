#ifndef FEEDEXPLORER_H
#define FEEDEXPLORER_H

#include "FeedArticle.hpp"
#include <string>
class FeedExplorer
{
    public:
        FeedExplorer(std::string filename);
        FeedExplorer& operator>>(FeedArticle& article);
        operator bool() const;
    protected:
    private:
        std::string filename;
        std::string allData;
        int lastPos;
        bool isRead;
        bool isDone;
};

#endif // FEEDEXPLORER_H
