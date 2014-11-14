#include <iostream>
#include <fstream>
#include <cstring>
#include "Stemmer.h"
#include "rapidxml-1.13/rapidxml.hpp"
#include "rapidxml-1.13/rapidxml_utils.hpp"
#include "avltree.h"

using namespace std;
using namespace rapidxml;

int main(int argc, char *argv[])
{

      file<> xmlFile("test.xml");
      xml_document<> doc;
      doc.parse<0>(xmlFile.data());
      xml_node<> *mainNode = doc.first_node();
      xml_node<> *currentPage = mainNode->first_node()->next_sibling("page");
      xml_node<> *textNode;

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

        /*
    int counter = 0;
>>>>>>> f7786a86e42f7973b582d0ad4ad9c97289b70c55
    while(currentPage != NULL)
    {
        textNode = currentPage->first_node("revision")->first_node("text");
        cout << textNode->value() << "\n\n\n\n\n\n" << endl;
        currentPage = currentPage->next_sibling();
        ++counter;
    }
    cout << counter << endl;
    */
    return 0;
}
