#ifndef WORD_H
#define WORD_H
#include <vector>



class Word
{
private:

    char *word;
    std::vector<int> lengthOfDoc; // Holds the length to extract from my user created file
    std::vector<int> beginningPos; // These are all parallel!
    std::vector<int> frequency;


public:

    Word(char *, int, int, int);
    ~Word();
    char *getWord();
};

#endif // WORD_H
