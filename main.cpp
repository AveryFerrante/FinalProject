#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include "rapidxml-1.13/rapidxml.hpp"
#include "rapidxml-1.13/rapidxml_utils.hpp"

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

    char* textBody = currentPage->first_node("revision")->first_node("text")->value();
    cout << textBody << endl;

    int counter = 10;
    while(currentPage != NULL)
    {
        textNode = currentPage->first_node("revision")->first_node("text");
        cout << textNode->value() << "\n\n\n\n\n\n" << endl;
        currentPage = currentPage->next_sibling();
        ++counter;
    }
    cout << counter << endl;

    return 0;
}