#include "documentindex.h"

using namespace std;

DocumentIndex::DocumentIndex() {}

void DocumentIndex::addDoc(int index) { fileStartPositions.push_back(index); }

void DocumentIndex::getDocument(int index)
{
    ifstream outputFile("file.txt", ios::binary);

    int length = fileStartPositions[index + 1] - fileStartPositions[index];
    char *word = new char[length + 1];

    outputFile.seekg(fileStartPositions[index]);
    outputFile.read(word, length);
    word[length] = '\0';

    cout << word << endl;
    delete [] word;
    outputFile.close();
}

void DocumentIndex::getTitle(int index)
{
    ifstream outputFile("file.txt", ios::binary);
    int length = fileStartPositions[index + 1] - fileStartPositions[index];
    char *word = new char[length + 1];

    outputFile.seekg(fileStartPositions[index]);
    outputFile.getline(word, length);

    cout << word;
    delete [] word;
    outputFile.close();
}

void DocumentIndex::writeOutIndex()
{
    ofstream outputFile(DOCUMNET_INDEX_FILE_PATH);
    for(size_t i = 0; i < fileStartPositions.size(); ++i)
        outputFile << fileStartPositions[i] << " ";
    outputFile.close();
}

void DocumentIndex::buildFromIndex()
{
    try
    {
        ifstream inputFile(DOCUMNET_INDEX_FILE_PATH);
        int temp = 0;
        while(!inputFile.eof())
        {
            inputFile >> temp;
            fileStartPositions.push_back(temp);
        }
    }
    catch(...)
    {
        throw ERROR_BUILDING_DOCUMENT_INDEX;
    }

}

int DocumentIndex::size() { return fileStartPositions.size(); }
int DocumentIndex::lastFile() { return fileStartPositions[fileStartPositions.size() - 1]; }
