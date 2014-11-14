#ifndef DOCUMENT_H
#define DOCUMENT_H
#include <vector>

class Document
{
private:

    char *title;
    std::vector<char *> body;

public:
    Document();
};

#endif // DOCUMENT_H
