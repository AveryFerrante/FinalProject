#ifndef DOCUMENTINDEX_H
#define DOCUMENTINDEX_H
#include <vector>
#include <fstream>
#include <iostream>

class DocumentIndex
{
private:
    std::vector<int> fileStartPositions; // Holds the getp() values when writing out so I can use this later to look up docs.
public:
    DocumentIndex();

    void addDoc(int);

    void getDocument(int);

};

#endif // DOCUMENTINDEX_H
