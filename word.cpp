#include "word.h"

Word::Word(char *&wordToAdd, Document &doc)
{
    word = wordToAdd;
    totalFrequency = 1;

    capacity = 5;
    docList = new Document[capacity];
    docList[0] = doc;
    size = 1;
}

Word::~Word()
{
    delete [] word;
}

void Word::addDocument(Document &doc)
{
    if(size == capacity)
        resizeDocs();

    docList[size] = doc;
}

void Word::resizeDocs()
{

}



char*& Word::getWord() { return word; }


