#ifndef DOCUMENT_H
#define DOCUMENT_H
#include <vector>
#include <iostream>

class Document
{
private:

    char *title;
    std::vector<char *> body;

public:
    Document();
    Document(char *);

    void addWord(char *);
    void setTitle(char *);

    void printBody();

};

#endif // DOCUMENT_H
