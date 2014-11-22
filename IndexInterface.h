#ifndef INDEXINTERFACE_H
#define INDEXINTERFACE_H
#include <vector>
#include "document.h"
#include "word.h"

//template<typename Tt>
class IndexInterface{
public:

    virtual void addWordToIndex(Word *data) = 0;
    virtual std::vector<int>* getDocumentsForWord(char*& word) = 0;
    virtual bool alreadyContains(char*& word, int documentNumber) = 0;
    virtual ~IndexInterface();
};

#endif // INDEXINTERFACE_H
