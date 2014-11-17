#ifndef WORD_H
#define WORD_H
#include <vector>



class Word
{
private:

    char *word;
    std::vector<char *> idList;
    std::vector<int> frequency; // Parallel to idList, holds # of time word appears in document


public:

    Word(char *, int, char *);
    ~Word();
    char*& getWord();
    void addDoc(char *, int);

};

#endif // WORD_H
