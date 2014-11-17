#ifndef PARSER_H
#define PARSER_H
#include <cstring>
#include <vector>
#include <string>
#include "word.h"
#include <iostream>
#include <fstream>
#include <algorithm> //For the remove function
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
    rapidxml::xml_node<> *idOfFile;
    rapidxml::xml_document<> xmlFile;

    int numberOfDocumentsInFile;

private: // Utility Functions

    void initializeMainNode();
    void initializeCurrentPage();
    void getNextPage();
    void getTitle();
    void getText();
    void getId();

    void removeNonAlphaCharacters(char *&);
    void writeToFile(std::ofstream &);

public:
    Parser(char *&);

    void printNodeContents();
    void getPageInfo();
    void cleanBodyContents();
    void createWordObjs();

    void parse(int);
};

#endif // PARSER_H
