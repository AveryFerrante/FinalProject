#include <iostream>
#include <fstream>
#include <cstring>
#include <ctype.h>
#include <algorithm>
#include "Stemmer.h"
#include "rapidxml-1.13/rapidxml.hpp"
#include "rapidxml-1.13/rapidxml_utils.hpp"
#include "avltree.h"
#include "parser.h"

using namespace std;


int main(int argc, char *argv[])
{

    //DID THIS PUSH WORK!!!!!
    Parser parse(argv[1]);
    parse.parse(10);

    /* JUST TEST STUFF IGNORE THIS BUT PLEASE DONT DELETE
    char *word = new char[5];
    word[0] = 'a';
    word[1] = '#';
    word[2] = ' ';
    word[3] = 'g';
    word[4] = '\0';

    int beg = strlen(word);
    cout << word << endl;
    char *stuff = strchr(word, ' ');
    *stuff = '\0';
    for(int i = 0; i < strlen(word); ++i)
    {
        if(!isalpha(word[i]))
            *(std::remove(word, word + strlen(word), word[i--])) = 0;
    }
    int end = strlen(word);
    *(stuff - (beg - end)) = ' ';
    cout << word << endl;
    */

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

    //IndexInterface testIndex;


    return 0;
}
