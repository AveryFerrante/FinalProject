#ifndef WORD_H
#define WORD_H
#include <vector>
#include <cstring>



class Word
{
private:

    char *word;
    std::vector<int> index; // This will hold the corresponding index to the docKey vector for where a file starts
    std::vector<int> frequency;


public:

    Word(char *, int, int);
    ~Word();
    char *getWord();

    void addDocIndex(int);
    int getDocIndex(int);
    std::vector<int> & getIndex();
};

#endif // WORD_H
