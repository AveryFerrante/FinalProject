#ifndef WORD_H
#define WORD_H
#include <vector>
#include <cstring>
#include <iostream>
#include <cassert>
#include <fstream>

#define MAX_RESULTS 14


class Word
{
private:
    char *word;
    int lastDocument;
    std::vector<int>* index; // This will hold the corresponding index to the docKey vector for where a file starts
    std::vector<int>* frequency;



public:

    Word(char *);
    Word(char *, int);
    ~Word();
    char *getWord();

    void addDocIndex(int);
    void addFreq(int);
    int getDocIndex(int);

    std::vector<int>* getIndex();
    std::vector<int>* getFreq();

    void updateFreqAndDoc(int);
    void sortRelevancy();

    void writeOutIndex(std::ofstream &);

    bool operator<(Word &);
    bool operator>(Word &);
};

#endif // WORD_H
