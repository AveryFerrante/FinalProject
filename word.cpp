#include "word.h"

Word::Word(char *wordToAdd, int freq, int docLength, int startPos)
    : word(wordToAdd)
{
    frequency.push_back(freq);
    beginningPos.push_back(startPos);
    lengthOfDoc.push_back(docLength);
}

Word::~Word()
{
    delete [] word;
    beginningPos.clear();
    frequency.clear();
    lengthOfDoc.clear();
}

char* Word::getWord() { return word; }


