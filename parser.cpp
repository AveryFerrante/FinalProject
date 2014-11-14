#include "parser.h"
#include <iostream>

using namespace rapidxml;
using namespace std;

Parser::Parser(char *&xmlFileName)
{
    file<> file(xmlFileName);
    xmlFile.parse<0>(file.data());

    //Set the two nodes up
    initializeMainNode();
    initializeCurrentPage();
    getText();
    getTitle();
}

void Parser::update() // Just a function for testing the class, not needed
{
    printNodeContents();
    getNextPage();
    while(currentPage != NULL)
    {
        getText();
        getTitle();
        printNodeContents();
        getNextPage();
    }
}



void Parser::printNodeContents()
{
    cout << "Title: " << titleOfFile->value() << endl;
    cout << "Body Contents:\n\n\n" << bodyOfFile->value() << endl;
}



void Parser::cleanBodyContents()
{
    char *bodyContents = bodyOfFile->value();
    char *whatsLeft = strchr(bodyContents, ' '); // Gets occurence to first space in the body

    Document *thisDoc = new Document;
    thisDoc->title = titleOfFile->value();

    while(whatsLeft != NULL)
    {
        // Logic for removing bogus characters/maybe even entire words

        *whatsLeft = '\0'; // Sets the word. bodyContents now is now a null terminated word.

         // bodyContents[Stemmer::stem(bodyContents, 0, strlen(bodyContents))] = '\0'; NEED STEMMER TO WORK

        thisDoc->body.push_back(bodyContents); // Adds the single word to the vector
        bodyContents = ++whatsLeft; // Point to beginning of next word
        whatsLeft = strchr(bodyContents, ' ');
    }

    for(int i = 0; i < thisDoc->body.size(); ++i)
        cout << thisDoc->body[i] << " ";

    //CREATE WORD OBJECT HERE SOMEWHERE
}







// **********UTILITY FUNCTIONS**********
void Parser::getText() { bodyOfFile = currentPage->first_node("revision")->first_node("text"); }
void Parser::getTitle() { titleOfFile = currentPage->first_node("title"); }
void Parser::getNextPage() { currentPage = currentPage->next_sibling(); }
void Parser::initializeCurrentPage() { currentPage = mainNode->first_node()->next_sibling("page"); }
void Parser::initializeMainNode() { mainNode = xmlFile.first_node(); }
