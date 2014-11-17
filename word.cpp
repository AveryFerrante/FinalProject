#include "word.h"

Word::Word(char *wordToAdd, int freq, char *id)
    : word(wordToAdd) { frequency.push_back(freq);
                        idList.push_back(id); }

Word::~Word()
{
    delete [] word;
    idList.clear();
    frequency.clear();
}

void Word::addDoc(char *id, int freq) { idList.push_back(id); frequency.push_back(freq); }

char*& Word::getWord() { return word; }


