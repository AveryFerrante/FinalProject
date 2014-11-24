#ifndef HASHTABLE_H
#define HASHTABLE_H
#include <string>

class HashTable
{
private:
    static const unsigned int tablesize = 100;
public:
    HashTable();
    int hash(std::string key);
};

#endif // HASHTABLE_H
