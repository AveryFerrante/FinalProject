#include "word.h"
using namespace std;

Word::Word(char *wordToAdd, int documentNumber)
{
    int length = strlen(wordToAdd);
    if(length > 100)
        cout << "Debug" << endl;
    word = new char[length + 1];
    strcpy(word, wordToAdd);
    word[length] = '\0';

    frequency = new vector<int>();
    index = new vector<int>();

    lastDocument = documentNumber;

    frequency->push_back(1); // When created, we know there is a frequency of atleast one
    index->push_back(documentNumber);
}

Word::Word(char *wordToAdd) // Used when the datastructure is being built from index
{
    word = wordToAdd;
    lastDocument = -1;

    index = new vector<int>();
    frequency = new vector<int>();
}

Word::~Word()
{
   // cout << this->word << " ";
    delete [] word;
    delete index;
    delete frequency;
}


void Word::sortRelevancy()
{
    assert ( index->size() == frequency->size() );

    int biggestIndex = 0;
    for(size_t x = 0; x < index->size(); ++x)
    {
        for(size_t i = x; i < frequency->size(); ++i)
        {
            if((*frequency)[i] > (*frequency)[biggestIndex])
                biggestIndex = i;

        }
        // Swap
        int temp;

        temp = (*frequency)[x];
        (*frequency)[x] = (*frequency)[biggestIndex];
        (*frequency)[biggestIndex] = temp;

        temp = (*index)[x];
        (*index)[x] = (*index)[biggestIndex];
        (*index)[biggestIndex] = temp;
    }
}

void Word::updateFreqAndDoc(int documentNumber)
{

    assert( this != NULL );

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

void Word::writeOutIndex(ofstream &outputFile)
{
    outputFile << strlen(word) << " " << word << " ";

    assert ( index->size() == frequency->size() );

    for(size_t i = 0; i < index->size(); ++i)
        outputFile << (*index)[i] << " " << (*frequency)[i] << " ";

    outputFile << "-1" << endl; // Null terminator
}

bool Word::operator<(Word &source)
{
    if(strcmp(word, source.getWord()) < 0)
        return true;
    else
        return false;
}

bool Word::operator>(Word &source)
{
    return !((*this) < source);
}

std::vector<int>* Word::getIndex() { return index; }
std::vector<int>* Word::getFreq() { return frequency; }
void Word::addDocIndex(int docIndex) { index->push_back(docIndex); }
void Word::addFreq(int freq) {frequency->push_back(freq); }
int Word::getDocIndex(int docIndex) { return (*index)[docIndex]; }
char* Word::getWord() { return word; }


