#ifndef INDEXINTERFACE_H
#define INDEXINTERFACE_H
#include <vector>
#include "document.h"
#include "word.h"

//template<typename T>
class IndexInterface{
public:

    virtual void addWordToIndex(Word word) = 0;
    virtual std::vector<Document> getDocumentsForWord(Word word) = 0;
    virtual ~IndexInterface();
};

#endif // INDEXINTERFACE_H
