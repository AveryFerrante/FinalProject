#ifndef PARSER_H
#define PARSER_H
#include <cstring>
#include <vector>
#include "rapidxml-1.13/rapidxml.hpp"
#include "rapidxml-1.13/rapidxml_utils.hpp"

class Parser
{

private: // Member Variables

    //Variables related to rapidxml
    rapidxml::xml_node<> *mainNode;
    rapidxml::xml_node<> *currentPage;
    rapidxml::xml_node<> *bodyOfFile;
    rapidxml::xml_node<> *titleOfFile;
    rapidxml::xml_document<> xmlFile;

public:
    //This is public so that the word class can have direct pointers to it
    struct Document
    {
        char *title;
        std::vector<char *> body;
    };

private: // Utility Functions

    void initializeMainNode();
    void initializeCurrentPage();
    void getNextPage();
    void getTitle();
    void getText();

public:
    Parser(char *&);

    void printNodeContents();
    void update();
    void cleanBodyContents();
};

#endif // PARSER_H
