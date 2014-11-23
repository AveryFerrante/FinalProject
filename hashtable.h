#ifndef HASHTABLE_H
#define HASHTABLE_H
#include <string>

class HashTable
{
private:
    static const unsigned int tablesize;
public:
    HashTable();
    int hash(std::string key);
};

#endif // HASHTABLE_H
