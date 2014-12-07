#ifndef INDEXINTERFACE_H
#define INDEXINTERFACE_H
#include <vector>
#include "word.h"

#define WORD_INDEX_FILE_PATH "wordindex.jaf"
#define ERROR_BUILDING_INDEX 101

//Contains functions common to the AVLTree and HashTable structures
class IndexInterface{
public:

    //Adds a word to the structure
    virtual void addWordToIndex(Word *data) = 0;

    //returns the document list for a given word
    virtual std::vector<DocumentAndFrequency *>* getDocumentsForWord(char*& word) = 0;

    //Boolean tha returns true if a word to be indexed is alreay in the structure
    virtual bool alreadyContains(char*& word, int documentNumber) = 0;

    //Writes the structure to the disk in the form of an index
    virtual void writeOutIndex() = 0;

    //Rebuilds the structure using the index that was written out
    virtual void buildFromIndex() = 0;

    //Obligatory destructor
    virtual ~IndexInterface();
};

#endif // INDEXINTERFACE_H
