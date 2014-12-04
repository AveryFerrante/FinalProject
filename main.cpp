#include <chrono>
#include <ctime>
#include "maintenancemode.h"
#include "interactivemode.h"
#include "parser.h"
#include "avltree.h"


using namespace std;
using namespace rapidxml;

int main(int argc, char *argv[])
{
//    Stemmer2 stemObj;
//    avltree tree;
//    Parser parse(argv[argc-1]);
//    parse.parse(argv[1], tree);

//    DocumentIndex index;
//    parse.writeToFile(index);

//    vector<DocumentAndFrequency *> *info = NULL;
//    char *word = new char[9];
//    strcpy(word, "computer");
//    word[8] = '\0';

//    word[stemObj.stem(word, 0, strlen(word) - 1)] = '\0';
//    info = tree.getDocumentsForWord(word);

//    if(info == NULL)
//        cout << "NULL" << endl;
//    for(int i = 0; i < info->size(); ++i)
//        cout << ((*info)[i])->getDocNumb() <<  " " << ((*info)[i])->getFreq() << endl;

    int decision = -1;
    while(decision != 0)
    {
        cout << "Please select a mode: " << endl;
        cout << "0. Exit\n1. Maintenance Mode\n2. Interactive Mode" << endl;
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

    }

    return 0;
}
