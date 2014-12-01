#ifndef INDEXINTERFACE_H
#define INDEXINTERFACE_H
#include <vector>
#include "word.h"

#define WORD_INDEX_FILE_PATH "wordindex.jaf"
#define ERROR_BUILDING_INDEX 101


class IndexInterface{
public:

    virtual void addWordToIndex(Word *data) = 0;
    virtual std::vector<int>* getDocumentsForWord(char*& word, std::vector<int>*& freqList) = 0;
    virtual bool alreadyContains(char*& word, int documentNumber) = 0;
    virtual void writeOutIndex() = 0;
    virtual void buildFromIndex() = 0;
    virtual ~IndexInterface();
};

#endif // INDEXINTERFACE_H
