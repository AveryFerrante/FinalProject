#include "document.h"

using namespace std;

Document::Document(char *docTitle)
 : title(docTitle) {}

Document::Document() { title = NULL; }


void Document::addWord(char *word) { body.push_back(word); }
void Document::setTitle(char *docTitle) { title = docTitle; }

void Document::printBody()
{
    for(int i = 0; i < body.size(); ++i)
        cout << body[i] << " ";
    cout << endl;
}


