#include <chrono>
#include <ctime>
#include "searchengine.h"
#include "hashtable.h"
#include "IndexInterface.h"
#include "maintenancemode.h"
#include "interactivemode.h"
#include "parser.h"
#include "avltree.h"


using namespace std;
using namespace rapidxml;

int main(int argc, char *argv[])
{


    cout << "Please select a mode: " << endl;
    cout << "0. Exit\n1. Maintenance Mode\n2. Interactive Mode" << endl;
    int decision;
    cin >> decision;

    if(decision == 1)
    {
        MaintenanceMode mode(argc, argv);
        mode.run();
    }
    else if(decision == 2)
    {
        InteractiveMode mode(argc, argv);
        mode.run();
    }
    else
        cout << "Unknown Input. Exiting...." << endl;


//    IndexInterface* structure = new HashTable();
//    HashTable* hashStructure = new HashTable();
//    hashStructure->printTable();
//    Word* word = new Word("cat");
//    Word* word2 = new Word("cat");
//    Word* word3 = new Word("cat");
//    Word* word4 = new Word("sandwich");
//    hashStructure->addWordToIndex(word);
//    hashStructure->addWordToIndex(word2);
//    hashStructure->addWordToIndex(word3);
//    hashStructure->addWordToIndex(word4);
//    hashStructure->printTable();

    //Parser parseThing(argv[argc - 1]);
    //avltree *avlTree = new avltree;
    //parseThing.parse(argv[argc - 2], *avlTree);
    //avlTree->display(avlTree->getRoot());
    //cout << "Done" << endl;
    //delete avlTree;
    //SearchEngine engine(argc, argv);
    //engine.runEngine();







    // This gets the user input and junk
//    for(int i = 0; i < 100; ++i){
//        int decision = -1;
//        while(decision != 0)

//        {
//            cout << "Please select a mode: " << endl;
//            cout << "0. Exit\n1. Maintenance Mode\n2. Interactive Mode" << endl;
//            cin >> decision;
//            if(decision == 1)
//            {
//                MaintenanceMode mode(argc, argv);
//                mode.run();
//            }
//            else if(decision == 2)
//            {
//                InteractiveMode mode(argc, argv);
//                mode.run();
//            }

//        }
//    }
    return 0;
}
