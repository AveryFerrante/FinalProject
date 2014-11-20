#ifndef PARSER_H
#define PARSER_H
#include <iostream>
#include <cstring>
#include <algorithm> //For the remove function
#include "rapidxml-1.13/rapidxml.hpp"
#include "rapidxml-1.13/rapidxml_utils.hpp"
#include "word.h"

class Parser
{

private: // Member Variables

    //Variables related to rapidxml
    rapidxml::file<> *xFile; // Must be a pointer else I will lose the file once it leaves the scope of the constructor
    rapidxml::xml_node<> *mainNode;
    rapidxml::xml_node<> *currentPage;
    rapidxml::xml_node<> *bodyOfFile;
    rapidxml::xml_node<> *titleOfFile;
    rapidxml::xml_node<> *idOfFile;
    rapidxml::xml_document<> xmlFile;

    int seekPosition;
    std::vector<char *> stopWords;

    std::vector<std::string> fileBodies;
    std::vector<std::string> fileTitles;
    std::vector<int> fileStartPosition;

private: // Utility Functions

    void initializeMainNode();
    void initializeCurrentPage();
    void getNextPage();
    void getTitle();
    void getText();
    void getId();
    void getPageInfo();

    void removeNonAlphaCharacters(char *&);
    void writeDataToVectors();
    void initializeStopWordList(const char *);

public:
    Parser(char *, char *);
    bool isStopWord(char *) const;

    void printNodeContents();
    void cleanBodyContents();
    void createWordObjs();

    void parse();

    void getFile(int);
};

#endif // PARSER_H
