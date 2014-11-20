#include "avltree.h"
#include "parser.h"
#include "documentindex.h"
#include <chrono>
#include <ctime>

using namespace std;
using namespace rapidxml;

int main(int argc, char *argv[])
{

    chrono::time_point<std::chrono::system_clock> start, end;
    start = chrono::system_clock::now();

    DocumentIndex documentIndexObject;
    Parser parse(argv[1], argv[2]);
    parse.parse(documentIndexObject);
    documentIndexObject.getDocument(32);

    end = chrono::system_clock::now();
    chrono::duration<double> elapsed_seconds = end-start;
    cout << "Elapsed file load time: " << elapsed_seconds.count() << endl;

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


    IndexInterface* testIndex = new avltree<Word>;



    return 0;
}
