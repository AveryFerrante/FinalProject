#ifndef WORD_H
#define WORD_H
#include "document.h"
class Word
{
private:
    char* word;
    Document* docList;
    int totalFrequency;
    int capacity;
    int size;


public:
    Word(char *&, Document &);
    ~Word();
    char*& getWord();
    void addDocument(Document &);
    void resizeDocs();

};

#endif // WORD_H
