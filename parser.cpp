#include "parser.h"

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

    numberOfDocumentsInFile = 0;
}

void Parser::getPageInfo() // Just a function for testing the class, not needed
{
    getText();
    getTitle();
    getId();
}



void Parser::printNodeContents()
{
    cout << "Title: " << titleOfFile->value() << endl;
    cout << "Body Contents:\n\n\n" << bodyOfFile->value() << endl;
}



void Parser::cleanBodyContents(/*this will eventually take a Document as an arg since this will be a util function*/)
{
    char *bodyContents = bodyOfFile->value();
    char *whatsLeft = strchr(bodyContents, ' '); // Gets occurence to first space in the body


    while(whatsLeft != NULL)
    {
        // Logic for removing bogus characters/maybe even entire words

        *whatsLeft = '\0';

        int beginning = strlen(bodyContents);
        removeNonAlphaCharacters(bodyContents);
        // bodyContents[Stemmer::stem(bodyContents, 0, strlen(bodyContents))] = '\0'; NEED STEMMER TO WORK
        int end = strlen(bodyContents);

        *(whatsLeft - (beginning - end)) = ' '; // Never actually alter bodyContents, just temporarily. Still need to alphabetize
        bodyContents = ++whatsLeft; // Point to beginning of next word
        whatsLeft = strchr(bodyContents, ' ');
    }

}

void Parser::parse(int splitNumber)
{
    char fileNames = 'a';
    string indexFileName = "index.txt";
    ofstream currentOutputFile(&fileNames);
    ofstream indexOutputFile(indexFileName.c_str());

    while(currentPage != NULL)
    {
        getPageInfo();

        writeToFile(currentOutputFile);
        ++numberOfDocumentsInFile;

        cleanBodyContents();
        printNodeContents();

        if(numberOfDocumentsInFile == splitNumber)
        {
            indexOutputFile << fileNames << "\n" << idOfFile->value() << endl;
            ++fileNames;
            numberOfDocumentsInFile = 0;
            currentOutputFile.close();
            currentOutputFile.open(&fileNames);
        }
        getNextPage();
    }

    currentOutputFile.close();

    indexOutputFile << fileNames << "\n" << idOfFile->value() << endl;
    indexOutputFile.close();

}



// **********UTILITY FUNCTIONS**********
void Parser::removeNonAlphaCharacters(char *&word)
{
    for(int i = 0; i < strlen(word); ++i)
    {
        word[i] = tolower(word[i]);

        if(!isalpha(word[i]))
            *(std::remove(word, word + strlen(word), word[i--])) = 0;
    }
}

void Parser::writeToFile(ofstream &outFile)
{
    outFile << idOfFile->value() << "\n" << titleOfFile->value()
            << "\n" << bodyOfFile->value() << "\n~" << endl;
}





void Parser::getText() { bodyOfFile = currentPage->first_node("revision")->first_node("text"); }
void Parser::getTitle() { titleOfFile = currentPage->first_node("title"); }
void Parser::getNextPage() { currentPage = currentPage->next_sibling(); }
void Parser::getId() { idOfFile = currentPage->first_node("id"); }
void Parser::initializeCurrentPage() { currentPage = mainNode->first_node()->next_sibling("page"); }
void Parser::initializeMainNode() { mainNode = xmlFile.first_node(); }
