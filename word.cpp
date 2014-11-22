#include "word.h"
using namespace std;

Word::Word(char *wordToAdd, int documentNumber)
{
    int length = strlen(wordToAdd);
    word = new char[length + 1];
    strcpy(word, wordToAdd);
    word[length] = '\0';

    frequency = new vector<int>();
    index = new vector<int>();

    lastDocument = documentNumber;

    frequency->push_back(1); // When created, we know there is a frequency of atleast one
    index->push_back(documentNumber);
}

Word::~Word()
{
    delete [] word;
}

bool Word::operator<(Word &source)
{
    if(strcmp(word, source.getWord()) < 0)
        return true;
    else
        return false;
}

void Word::updateFreqAndDoc(int documentNumber)
{

    assert(this != NULL);

    if(lastDocument == documentNumber) // Still on the same document, just need to add one to the frequency
            (*frequency)[frequency->size() - 1] += 1;
    else // On a new document, need to add it to the vector and start a frequency for it
    {
        assert(index != NULL);
        index->push_back(documentNumber); // The document we are currently on

        assert(frequency != NULL);
        frequency->push_back(1); // We have atleast one occurence
        lastDocument = documentNumber; // Update this so we can just add to frequency if it occurs again in this document
    }

}

bool Word::operator>(Word &source)
{
    return !(*this < source);
}

std::vector<int>* Word::getIndex() { return index; }
void Word::addDocIndex(int docIndex) { index->push_back(docIndex); }
int Word::getDocIndex(int docIndex) { return (*index)[docIndex]; }
char* Word::getWord() { return word; }


