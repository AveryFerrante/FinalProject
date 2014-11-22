#ifndef WORD_H
#define WORD_H
#include <vector>
#include <cstring>
#include <iostream>
#include <cassert>


class Word
{
private:
    char *word;
    int lastDocument;
    std::vector<int>* index; // This will hold the corresponding index to the docKey vector for where a file starts
    std::vector<int>* frequency;



public:

    Word(char *, int);
    ~Word();
    char *getWord();

    void addDocIndex(int);
    int getDocIndex(int);
    std::vector<int>* getIndex();

    void updateFreqAndDoc(int);

    bool operator<(Word &);
    bool operator>(Word &);
};

#endif // WORD_H
