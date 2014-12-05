#include "word.h"
using namespace std;

Word::Word(char *wordToAdd, int documentNumber)
{
    word = new char[strlen(wordToAdd) + 1];
    strcpy(word, wordToAdd);

    information = new std::vector<DocumentAndFrequency *>();
    DocumentAndFrequency *temp = new DocumentAndFrequency(documentNumber, 1);
    information->push_back(temp);

    lastDocument = documentNumber;
}

Word::Word(string &wordToAdd, int length) // Used when the datastructure is being built from index
{
    char *tempWord = new char[length + 1];
    strcpy(tempWord, wordToAdd.c_str());

    word = tempWord;
    lastDocument = -1; // Should never need to use this when building from an index

    information = new vector<DocumentAndFrequency *>();
}

Word::~Word()
{
    delete [] word;

    for(size_t i = 0; i < information->size(); ++i)
        delete (*information)[i];
    delete information;
}

void Word::addInfo(int docId, int freq) // Used when building from the index
{
    DocumentAndFrequency *temp = new DocumentAndFrequency(docId, freq);
    information->push_back(temp);
}


void Word::sortRelevancy()
{
    // SORT BY DOCUMENT ID VALUE HERE, NOT BY FREQUENCY VALUE!
    std::sort(information->begin(), information->end(), DocumentAndFrequency::ascendingByDocID);
}

void Word::updateFreqAndDoc(int CurrentDocumentNumber)
{

    assert( this != NULL );

    if(lastDocument == CurrentDocumentNumber) // Still on the same document, just need to add one to the frequency
        information->back()->increaseFreq();

    else // On a new document, need to add it to the vector and start a frequency for it
    {
        lastDocument = CurrentDocumentNumber; // Update this so we can just add to frequency if it occurs again in this document

        DocumentAndFrequency *temp = new DocumentAndFrequency(CurrentDocumentNumber, 1);
        information->push_back(temp);
    }

}

void Word::writeOutIndex(ofstream &outputFile)
{
    outputFile << strlen(word) << " " << word << " ";

    for(size_t i = 0; i < information->size(); ++i)
        outputFile << (*information)[i]->getDocNumb() << " " << (*information)[i]->getFreq() << " ";

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

std::vector<DocumentAndFrequency *>* Word::getInformation() { return information; }
char * Word::getWord() { return word; }
