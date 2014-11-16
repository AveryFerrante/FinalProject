#ifndef WORD_H
#define WORD_H
#include "parser.h"



class Word
{
private:

    char *word;
    Parser::Document *docList;
    int totalFrequency;
    int capacity;
    int size;


public:

    Word(char *, Parser::Document &);
    ~Word();
    char*& getWord();
    void addDocument(Parser::Document &);
    void resizeDocs();

};

#endif // WORD_H
