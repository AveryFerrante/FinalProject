#ifndef HASHTABLE_H
#define HASHTABLE_H
#include <string>
#include "word.h"
#include "IndexInterface.h"

class HashTable: public IndexInterface
{
private:
    static const unsigned int tablesize = 100;

    struct HashNode
    {
        Word* data;
        HashNode* next;
    };

    HashNode* table[tablesize];

public:
    HashTable();
    int hash(std::string key);
    void addWordToIndex(Word* word);
    std::vector<int>* getDocumentsForWord(char *&word, std::vector<int> *&freqList);
    bool alreadyContains(char *&word, int documentNumber);
    void writeOutIndex();
    void buildFromIndex(std::ifstream &inputFile);
    void addNode(Word*& word);
    int numberOfItemsInBucket(int index);

};

#endif // HASHTABLE_H
