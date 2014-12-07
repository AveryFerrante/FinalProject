#ifndef WORD_H
#define WORD_H
#include <vector>
#include <cstring>
#include <iostream>
#include <cassert>
#include <fstream>
#include "documentandfrequency.h"
#include <algorithm>

#define MAX_RESULTS 14 // Enter 1 less than you want displayed (i.e. 14 will display 1 - 15 results on the screen)

//Word class  that represents an entry in an index.
//Contains a cstring that is the word it self
//A vector pointer to the list of documents it has appeared in and how frequently
class Word
{
private:
    char *word;
    int lastDocument; // This is checked against the current document number to see if we only need to update the frequency
    // of the word or if we need to create a new documentandfrequency object for the word.

    std::vector<DocumentAndFrequency *> *information;
public:

    Word(std::string &wordToAdd, int length);
    Word(char *, int);
    ~Word();
    char *getWord();

    void addDocIndex(int);
    void addFreq(int);
    int getDocIndex(int);
    void addInfo(int, int);

    std::vector<DocumentAndFrequency *>* getInformation();

    void updateFreqAndDoc(int);
    void sortRelevancy();

    void writeOutIndex(std::ofstream &);

    bool operator<(Word &);
    bool operator>(Word &);
};

#endif // WORD_H
