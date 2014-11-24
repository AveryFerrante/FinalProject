#include "parser.h"

using namespace rapidxml;
using namespace std;

int Parser::k = 0, Parser::k0 = 0, Parser::j = 0 ;
char * Parser::b = NULL;

Parser::Parser(char *stopWordList)
{
    initializeStopWordList(stopWordList);
    documentCount = 0;
}
Parser::~Parser()
{

}

int Parser::stemWord(char *&word)
{
    return this->stem(word, 0, strlen(word) - 1);
}

void Parser::parse(char *&fileName, IndexInterface &dataStructure)
{
    // This initializes the file. Must be done here because if this goes out of scope, the whole file is lost.
    file<> xFile(fileName);
    xmlFile.parse<parse_no_utf8>(xFile.data());

    //Set the two nodes up
    initializeMainNode();
    initializeCurrentPage();

    while(currentPage != NULL)
    {
        getPageInfo();
        if(bodyOfFile->value_size() < 100)
        {
            getNextPage();
            continue;
        }

        writeDataToVectors();
        cleanBodyContents(dataStructure);
        getNextPage();
        ++documentCount;
    }
    clearCurrentDocument();
}



void Parser::writeToFile(DocumentIndex &documentIndexObject)
{
    ofstream outputFile("file.txt", ios::binary);
    documentIndexObject.addDoc(0);
    for(int i = 0; i < fileBodies.size(); ++i)
    {
        outputFile << *fileTitles[i] << endl;
        outputFile << *fileBodies[i] << endl;
        documentIndexObject.addDoc(outputFile.tellp());
    }
    documentIndexObject.addDoc(outputFile.tellp());
    outputFile.close();
}


// ********************************UTILITY FUNCTIONS****************************************************************************
void Parser::initializeStopWordList(const char *fileName)
{
    ifstream wordList(fileName);
    char *buffer = new char[81];

    while(!wordList.eof())
    {
        wordList.getline(buffer, 80);
        char *temp = new char[strlen(buffer)];
        strcpy(temp, buffer);
        stopWords.push_back(temp);
    }
    delete [] buffer;
    wordList.close();
}

void Parser::removeNonAlphaCharacters(char *&word)
{
    for(size_t i = 0; i < strlen(word); ++i)
    {
        word[i] = tolower(word[i]);

        if(!isalpha(word[i]))
            *(std::remove(word, word + strlen(word), word[i--])) = 0;
    }
}

void Parser::cleanBodyContents(IndexInterface &dataStructure)
{
    char *bodyContents = bodyOfFile->value();
    char *whatsLeft = strchr(bodyContents, ' '); // Gets occurence to first space in the body

    while(whatsLeft != NULL)
    {
        *whatsLeft = '\0';

        removeNonAlphaCharacters(bodyContents);
        if(strlen(bodyContents) <= 1 || strlen(bodyContents) >= 22 || isStopWord(bodyContents)) // Skip this word
        {
            bodyContents = ++whatsLeft; // Point to beginning of next word
            whatsLeft = strchr(bodyContents, ' ');
            continue;
        }

        bodyContents[this->stem(bodyContents, 0, strlen(bodyContents) - 1)] = '\0';

        createWordObjs(dataStructure, bodyContents);

        bodyContents = ++whatsLeft; // Point to beginning of next word
        whatsLeft = strchr(bodyContents, ' ');
    }
}

bool Parser::isStopWord(char *word) const
{
    int  left = 0, right = stopWords.size() - 1, mid;
    while (left <= right)
    {
        mid = ((left + right) / 2);

        if (strcmp(stopWords[mid], word) > 0) // word is less than
        {
            right = mid - 1;
            continue;
        }
        else if (strcmp(stopWords[mid], word) < 0) // word is greater than
        {
            left = mid + 1;
            continue;
        }
        else
            return true;
    }

    return false;
}

void Parser::createWordObjs(IndexInterface &dataStructure, char *&word)
{
    if(!dataStructure.alreadyContains(word, documentCount))
    {
        Word *temp = new Word(word, documentCount);
        dataStructure.addWordToIndex(temp);
    }
}

void Parser::writeDataToVectors()
{
    fileBodies.push_back(new string(bodyOfFile->value()));
    fileTitles.push_back(new string(titleOfFile->value()));
}

void Parser::getPageInfo() // Just a function for testing the class, not needed
{
    getTitle();
    getId();
    getText();
}

void Parser::clearCurrentDocument() { xmlFile.clear(); }
void Parser::getText() { bodyOfFile = currentPage->first_node("revision")->first_node("text"); }
void Parser::getTitle() { titleOfFile = currentPage->first_node("title"); }
void Parser::getNextPage() { currentPage = currentPage->next_sibling(); }
void Parser::getId() { idOfFile = currentPage->first_node("id"); }
void Parser::initializeCurrentPage() { currentPage = mainNode->first_node("page"); }
void Parser::initializeMainNode() { mainNode = xmlFile.first_node(); }
