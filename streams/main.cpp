#include <iostream>
#include "FeedExplorer.h"
#include "FeedArticle.hpp"
using namespace std;

int main()
{
    FeedExplorer f("feed.xml");
    int articlesFound = 0;
    FeedArticle a;
    while(articlesFound < 10000) {
        cout << "Looking for another feed article..." << endl;
        f >> a;
        if (!f) {
            cout << "End of feed!" << endl;
            break;
        }
        cout << "Article " << articlesFound << " found!" << endl << a << endl;
        articlesFound++;
    }
    if (articlesFound == 10000) {
        cout << "Found enough articles for now!" << endl;
    }
    return 0;
}
