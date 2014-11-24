#include "parser.h"
#include "documentindex.h"
#include "avltree.h"
#include <chrono>
#include <ctime>
#include <vector>

using namespace std;
using namespace rapidxml;

int main(int argc, char *argv[])
{
    cout << "TEST 1" << endl;
    chrono::time_point<std::chrono::system_clock> start, end;
    start = chrono::system_clock::now();

    DocumentIndex documentIndexObject;
    avltree dataStruct;

    Parser parse(argv[argc - 1]);
    for(int i = 1; i < argc - 1; ++i)
    {
        cout << "Opening file " << argv[i] << " for parsing" << endl;
        parse.parse(argv[i], dataStruct);
    }

    end = chrono::system_clock::now();
    chrono::duration<double> elapsed_seconds = end-start;
    cout << "Elapsed file load time: " << elapsed_seconds.count() << endl;

    parse.writeToFile(documentIndexObject);


    for(int i = 0; i < 5; ++i)
    {
        cout << "Input a word to search for." << endl;
        string userWord;
        cin >> userWord;
        char *word = new char[userWord.length() + 1];
        strcpy(word, userWord.c_str());
        word[userWord.length()] = '\0';

       // word[stem(word, 0, strlen(word) - 1)] = '\0';


        vector<int> *freqList = NULL;
        vector<int> *docList = dataStruct.getDocumentsForWord(word, freqList);

        if(docList != NULL)
        {
            for(int i = 0; i < docList->size(); ++i)
            {
                cout << i + 1 << ": ";
                documentIndexObject.getTitle((*docList)[i]);
                cout << " with " << (*freqList)[i] << " occurances of " << word << endl;
            }

            int userInput;
            cout << "Enter the number of the document you would like to see." << endl;
            cin >> userInput;

            documentIndexObject.getDocument((*docList)[userInput - 1]);
        }
        else
            cout << "Word not found." << endl;
    }


    return 0;
}
