#include "hashtable.h"

HashTable::HashTable()
{
    for(int i = 0; i < tablesize; i++)
    {
        table[i] =  new HashNode;
        table[i]->next = NULL;
        table[i]->data = NULL;
    }

}

int HashTable::hash(std::string key){

    return std::hash<std::string>(key);
    //int index = 0;
    //Just an idea

    //return index;
}

void HashTable::addNode(Word*& word)
{
    int index = hash(word->getWord());

    if(table[index]->data == NULL)
    {
        table[index]->data = word;
    }
    else
    {
        HashNode* tempPtr = table[index];
        HashNode* newNode = new HashNode;
        newNode->data = word;
        newNode->next = NULL;

        while(tempPtr->next !=  NULL){
            tempPtr = tempPtr->next;
        }

        tempPtr->next = newNode;
    }

}

bool HashTable::alreadyContains(char *&word, int documentNumber)
{

}

void HashTable::addWordToIndex(Word *word)
{

}

std::vector<int>* HashTable::getDocumentsForWord(char *&word, std::vector<int> *&freqList)
{

}

void HashTable::writeOutIndex()
{

}

void HashTable::buildFromIndex(std::ifstream &inputFile)
{

}
