#include <iostream>
#include <fstream>
#include <cstring>
#include <ctype.h>
#include <algorithm>
#include "rapidxml-1.13/rapidxml.hpp"
#include "rapidxml-1.13/rapidxml_utils.hpp"
#include "avltree.h"
#include "parser.h"

using namespace std;
using namespace rapidxml;

int main(int argc, char *argv[])
{
    Parser parse(argv[1]);
    parse.initializeStopWordList(argv[2]);
    parse.parse();
   // parse.getFile(0);

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
