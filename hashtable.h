#ifndef HASHTABLE_H
#define HASHTABLE_H
#include <string>
#include "word.h"
#include "IndexInterface.h"
#include <iostream>
#include <fstream>

class HashTable: public IndexInterface
{
private:
    static const unsigned int tablesize = 1000000;

    struct HashNode
    {
        Word* data;
        HashNode* next;

        ~HashNode() { delete data; }
    };

    HashNode* table[tablesize];

public:
    HashTable();
    ~HashTable();

    unsigned int hash(char* key);
    void addWordToIndex(Word* word);
    std::vector<DocumentAndFrequency *>* getDocumentsForWord(char *&word);
    bool alreadyContains(char *&word, int documentNumber);
    void writeOutIndex();
    void buildFromIndex();
    void addNode(Word*& word);
    void findWord(char* word);
    int numberOfItemsInBucket(int index);
    void write(std::ofstream &outputFile);
    void printTable();

};

#endif // HASHTABLE_H
