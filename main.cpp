#include <chrono>
#include <ctime>
#include "maintenancemode.h"
#include "interactivemode.h"


using namespace std;
using namespace rapidxml;

int main(int argc, char *argv[])
{
    InteractiveMode mode(argc, argv);
    mode.run();

    vector<vector<int> *> test;
    vector<int> *work = new vector<int>;
    work->push_back(1);
    work->push_back(2);
    test.push_back(work);

    cout << (*(test[0]))[1] << endl;




    /*
    avltree dataStruct;
    DocumentIndex documentIndexObject;
    dataStruct.buildFromIndex();
    documentIndexObject.buildFromIndex();

    //Parser parse(argv[argc - 1]);
    //parse.parse("add.xml", dataStruct);
    //parse.writeToFile(documentIndexObject);

    //dataStruct.writeOutIndex();
    //documentIndexObject.writeOutIndex();



    // This gets the user input and junk
    for(int i = 0; i < 100; ++i)
    {
        cout << "Input a word to search for." << endl;
        string userWord;
        cin >> userWord;
        char *word = new char[userWord.length() + 1];
        strcpy(word, userWord.c_str());
        word[userWord.length()] = '\0';

        Stemmer2 stemmer;
        word[stemmer.stem(word, 0, strlen(word) - 1)] = '\0';


        vector<int> *freqList = NULL;
        vector<int> *docList = dataStruct.getDocumentsForWord(word, freqList);

        if(docList != NULL && strlen(word) > 0)
        {
            for(int i = 0; i < docList->size(); ++i)
            {
                cout << i + 1 << ": ";
                documentIndexObject.getTitle((*docList)[i]);
                cout << " with " << (*freqList)[i] << " occurances of " << word << endl;
                if(i == 14)
                    break;
            }

            int userInput;
            cout << "Enter the number of the document you would like to see." << endl;
            cin >> userInput;

            documentIndexObject.getDocument((*docList)[userInput - 1]);
        }
        else
            cout << "Word not found." << endl;

        cout << endl;
    }
    */


    return 0;
}
