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
    static int documentNumber; // This is used to know when to add 1 to an already existing frequency or start a new freq.


public:

    Word(char *);
    ~Word();
    char *getWord();

    static void increaseDocNumber();

    void addDocIndex(int);
    int getDocIndex(int);
    std::vector<int>* getIndex();

    void updateFreqAndDoc();

    bool operator<(Word &);
    bool operator>(Word &);
};

#endif // WORD_H
