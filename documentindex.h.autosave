#ifndef DOCUMENTINDEX_H
#define DOCUMENTINDEX_H
#include <vector>
#include <fstream>
#include <iostream>
#include <string>

#define DOCUMNET_INDEX_FILE_PATH "documentindex.jaf"
#define ERROR_BUILDING_DOCUMENT_INDEX 1010

#define FILE_LOOK_UP "lookup.jaf"

//Object that represents the index that has been written to disk
class DocumentIndex
{
private:
    std::vector<int> fileStartPositions; // Holds the getp() values when writing out so I can use this later to look up docs.
public:
    DocumentIndex();

    void addDoc(int);

    void getDocument(int); // Takes the index number of the fileStartPositions that the document is contained at
    void getTitle(int);

    void writeOutIndex();
    void buildFromIndex();

    int size();
    int lastFile();
};

#endif // DOCUMENTINDEX_H
