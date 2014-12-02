#ifndef PARSER_H
#define PARSER_H
#include <iostream>
#include <cstring>
#include <algorithm> //For the remove function
#include "rapidxml-1.13/rapidxml.hpp"
#include "rapidxml-1.13/rapidxml_utils.hpp"
#include "word.h"
#include "documentindex.h"
#include "IndexInterface.h"
#include "stemmer2.h"

#define STOP_WORDS_FILE_OPEN_ERROR 11
#define XML_FILE_OPEN_ERROR 12

#define OUTPUT_FILE "lookup.jaf"

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

    std::vector<char *> stopWords;

    Stemmer2 stemObject;

    std::vector<std::string *> fileBodies;
    std::vector<std::string *> fileTitles;

    int documentCount;


private: // Utility Functions

    void initializeDocument(char *&);
    void initializeMainNode();
    void initializeCurrentPage();
    void getNextPage();
    void getTitle();
    void getText();
    void getId();
    void getPageInfo();

    void writeDataToVectors();
    void initializeStopWordList(const char *);

    // Thses deal with cleaning words from the body of the files
    void cleanBodyContents(IndexInterface &);
    bool isStopWord(char *) const;
    void removeNonAlphaCharacters(char *&);

    void createWordObjs(IndexInterface &, char *&);

    void clearCurrentDocument();

public:
    Parser(char *);
    ~Parser();
    void parse(const char *, IndexInterface &);

    void writeToFile(DocumentIndex &);
};

#endif // PARSER_H
