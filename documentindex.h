#ifndef DOCUMENTINDEX_H
#define DOCUMENTINDEX_H
#include <vector>
#include <fstream>
#include <iostream>
#include <string>

class DocumentIndex
{
private:
    std::vector<int> fileStartPositions; // Holds the getp() values when writing out so I can use this later to look up docs.
public:
    DocumentIndex();

    void addDoc(int);

    void getDocument(int);
    void getTitle(int);



};

#endif // DOCUMENTINDEX_H
