#include "word.h"

Word::Word(char *&wordToAdd, Parser::Document &doc)
{
    word = wordToAdd;
    totalFrequency = 1;

    capacity = 5;
    docList = new Parser::Document[capacity];
    docList[0] = doc;
    size = 1;
}

Word::~Word()
{
    delete [] word;
}

void Word::addDocument(Parser::Document &doc)
{
    if(size == capacity)
        resizeDocs();

    docList[size] = doc;
}

void Word::resizeDocs()
{

}



char*& Word::getWord() { return word; }


