#include "documentindex.h"

using namespace std;

DocumentIndex::DocumentIndex() {}

void DocumentIndex::addDoc(int index) { fileStartPositions.push_back(index); }

void DocumentIndex::getDocument(int index)
{
    ifstream outputFile("file.txt", ios::binary);

    int length = fileStartPositions[index + 1] - fileStartPositions[index];
    char *word = new char[length];

    outputFile.seekg(fileStartPositions[index]);
    outputFile.read(word, length);
    word[length] = '\0';

    cout << word << endl;
    delete [] word;
    outputFile.close();
}
