#include "word.h"
using namespace std;

int Word::documentNumber = 0; // This is the document we are currently on (i.e. the 5th doc). Updated in parser class

Word::Word(char *wordToAdd)
{
    int length = strlen(wordToAdd);
    word = new char[length];
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

void Word::updateFreqAndDoc()
{
    cout << "Updating frequency" << endl;

    assert(this != NULL);

    if(lastDocument == documentNumber) // Still on the same document, just need to add one to the frequency
            (*frequency)[frequency->size() - 1] += 1;
    else // On a new document, need to add it to the vector and start a frequency for it
    {
        if(documentNumber == 1 && strcmp(word, "material") == 0)
            cout << endl;

        assert(index != NULL);

        cout << "Starting new doc" << endl;
        index->push_back(Word::documentNumber); // The document we are currently on
        cout << "Pushed doc number" << endl;

        assert(frequency != NULL);

        frequency->push_back(1); // We have atleast one occurence
        cout << "Pushed frequency" << endl;
        lastDocument = documentNumber; // Update this so we can just add to frequency if it occurs again in this document
    }
    cout << "Successful" << endl;
}

void Word::increaseDocNumber() { ++documentNumber; }

bool Word::operator>(Word &source)
{
    return !(*this < source);
}

std::vector<int>* Word::getIndex() { return index; }
void Word::addDocIndex(int docIndex) { index->push_back(docIndex); }
int Word::getDocIndex(int docIndex) { return (*index)[docIndex]; }
char* Word::getWord() { return word; }


