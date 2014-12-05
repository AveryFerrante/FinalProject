#include "hashtable.h"

using namespace std;

HashTable::HashTable()
{
    for(size_t i = 0; i < tablesize; i++)
    {
        table[i] =  NULL;
    }
}

HashTable::~HashTable()
{
    cout << "Deleting Hash Table." << endl;
    for(size_t i = 0; i < tablesize; ++i)
    {
        HashNode *temp = table[i];
        while(temp != NULL)
        {
            HashNode *next = temp->next;
            delete temp;
            temp = next;
        }
    }
    cout << "Successfully deleted." << endl;
}

unsigned int HashTable::hash(char* key)
{

        unsigned int hashIndex = 5381;
        int c;

        while (c = *(key++))
            hashIndex = ((hashIndex << 5) + hashIndex) + c; /* hash * 33 + c */

        return hashIndex % tablesize;
}

void HashTable::addNode(Word*& word)
{
    int index = hash(word->getWord());

    if(table[index] == NULL)
    {
        table[index]= new HashNode;
        table[index]->data = word;
        table[index]->next = NULL;
    }
    else // Collision
    {
        HashNode* tempPtr = table[index];
        HashNode* newNode = new HashNode;
        newNode->data = word;
        newNode->next = NULL;

        while(tempPtr->next !=  NULL)
        {
            tempPtr = tempPtr->next;
        }
        tempPtr->next = newNode;
    }
}

bool HashTable::alreadyContains(char*& word, int documentNumber)
{
    int index = hash(word);
    HashNode* tempPtr = table[index];

    while(tempPtr != NULL)
    {
      if(strcmp(tempPtr->data->getWord(), word) == 0)
      {
          tempPtr->data->updateFreqAndDoc(documentNumber);
          return true;
      }
      tempPtr = tempPtr->next;
    }

    return false;
}

void HashTable::addWordToIndex(Word *word)
{
    addNode(word);
}

std::vector<DocumentAndFrequency *>* HashTable::getDocumentsForWord(char*& word)
{
    int index = hash(word);
    HashNode* tempPtr = table[index];

    while(tempPtr != NULL)
    {
      if(strcmp(tempPtr->data->getWord(), word) == 0)
          return tempPtr->data->getInformation();
      tempPtr = tempPtr->next;
    }

    return NULL;
}


void HashTable::writeOutIndex()
{
    ofstream outputFile(WORD_INDEX_FILE_PATH);
    write(outputFile);
    outputFile.close();
}

void HashTable::write(std::ofstream &outputFile)
{
    for(size_t i = 0; i < tablesize; i++)
    {
        HashNode* tempPtr = table[i];
        while(tempPtr != NULL)
        {
            tempPtr->data->writeOutIndex(outputFile);
            tempPtr = tempPtr->next;
        }
    }
}

void HashTable::printTable(){
    int number;
    for(size_t i = 0; i < tablesize; i++)
    {
        number = numberOfItemsInBucket(i);
        HashNode* tempPtr = table[i];
        while(tempPtr != NULL)
        {
            cout << "Index " << i << endl;
            cout << tempPtr->data->getWord() << endl;
            tempPtr = tempPtr->next;
        }
        if(number > 0)
            cout << number << endl;
    }

}

int HashTable::numberOfItemsInBucket(int index)
{

    int counter = 0;

    if(table[index] == NULL){
        return counter;
    }
    else
    {
        counter++;
        HashNode* ptr = table[index];
        while(ptr->next != NULL){
            ptr = ptr->next;
            counter++;
        }

        return counter;
    }
}

void HashTable::buildFromIndex()
{
    ifstream inputFile(WORD_INDEX_FILE_PATH);
    try
    {
        int tempFreq = 0;
        int tempIndex = 0;
        string size = "fill"; // This is a string so I can check to see if it is on a blank line (end of the document)
        string word;
        while(!inputFile.eof() && (inputFile >> size != "")) // This also loads the length of the word
        {
            inputFile >> word;
            Word *temp = new Word(word, atoi(size.c_str()));

            inputFile >> tempIndex; // File index first
            while(tempIndex != -1)
            {
                inputFile >> tempFreq; // Frequency
                temp->addInfo(tempIndex, tempFreq);
                inputFile >> tempIndex; // File Index (or terminator -1)
            }

            this->addWordToIndex(temp);
        }
    }
    catch(...)
    {
        inputFile.close();
        throw ERROR_BUILDING_INDEX;
    }

    inputFile.close();

}
