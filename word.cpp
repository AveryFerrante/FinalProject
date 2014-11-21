#include "word.h"

Word::Word(char *wordToAdd, int freq, int documentIndex)
{
    int length = strlen(wordToAdd);
    word = new char[length];
    strcpy(word, wordToAdd);
    word[length] = '\0';

    frequency.push_back(freq);
    index.push_back(documentIndex);
}

Word::~Word()
{
    delete [] word;
}
std::vector<int> & Word::getIndex() { return index; }
void Word::addDocIndex(int docIndex) { index.push_back(docIndex); }
int Word::getDocIndex(int docIndex) { return index[docIndex]; }
char* Word::getWord() { return word; }


