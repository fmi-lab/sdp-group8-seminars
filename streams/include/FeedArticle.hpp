#ifndef FEEDARTICLE_HPP
#define FEEDARTICLE_HPP

#include <string>
#include <ostream>
struct FeedArticle
{
    std::string title;
    std::string summary;
    std::string url;
    friend std::ostream& operator<<(std::ostream& out, const FeedArticle& article) {
        out << "Title: " << article.title;
        out << std::endl;
        out << "Find out more at: " << article.url;
        out << std::endl;
        return out;
    }
};

#endif // FEEDARTICLE_HPP
