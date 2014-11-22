#include "parser.h"
#include "documentindex.h"
#include "avltree.h"
#include <chrono>
#include <ctime>

using namespace std;
using namespace rapidxml;

int main(int argc, char *argv[])
{
    chrono::time_point<std::chrono::system_clock> start, end;
    start = chrono::system_clock::now();

    DocumentIndex documentIndexObject;
    avltree dataStruct;
    Parser parse(argv[1], argv[2]);
    parse.parse(documentIndexObject, dataStruct);

    end = chrono::system_clock::now();
    chrono::duration<double> elapsed_seconds = end-start;
    cout << "Elapsed file load time: " << elapsed_seconds.count() << endl;

    cout << "Input a word to search for." << endl;
    string userWord;
    cin >> userWord;
    const char *word = userWord.c_str();
    vector<int> *docList = dataStruct.getDocumentsForWord(word);

    for(int i = 0; i < docList->size(); ++i)
    {
        cout << i + 1 << ": ";
        documentIndexObject.getTitle((*docList)[i]);
    }

    int userInput;
    cout << "Enter the number of the document you would like to see." << endl;
    cin >> userInput;

    documentIndexObject.getDocument((*docList)[userInput - 1]);



    /*
        avltree<int> at ;
        AVLNode* avl = NULL ;
        int h ;

        cout << "Testing AVL building " << endl;
        for(int i = 1; i <= 625; i *= 5)
        {
            cout << endl;
            avl = at.insert(i,&h);
            at.setroot(avl);
            cout << endl;
            at.display ( avl ) ;
            cout << endl;
        }
            avl = at.deldata(avl,25,&h);
            at.setroot(avl);
            cout << endl;
            at.display(avl);
    */

    return 0;
}
