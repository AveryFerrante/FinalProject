#include "parser.h"

using namespace rapidxml;
using namespace std;

Parser::Parser(char *stopWordList)
{
    initializeStopWordList(stopWordList);
    documentCount = 0;
}

void Parser::printNodeContents()
{
    cout << "Title: " << titleOfFile->value() << endl;
    cout << "Body Contents:\n\n\n" << bodyOfFile->value() << endl;
}


void Parser::parse(char *&fileName, DocumentIndex &documentIndexObject, IndexInterface &dataStructure)
{
    initializeDocument(fileName);

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

        if(strlen(bodyContents) > 22 || isStopWord(bodyContents)) // Skip this word
        {
            bodyContents = ++whatsLeft; // Point to beginning of next word
            whatsLeft = strchr(bodyContents, ' ');
            continue;
        }

        removeNonAlphaCharacters(bodyContents);
        if(strcmp(bodyContents, "") == 0) // Possible for words to literally be empty, don't want to index those
        {
            bodyContents = ++whatsLeft;
            whatsLeft = strchr(bodyContents, ' ');
            continue;
        }
        //bodyContents[pstem::stem(bodyContents, 0, strlen(bodyContents) - 1)] = '\0';

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

void Parser::initializeDocument(char *&xmlFileName)
{
    xFile = new file<>(xmlFileName);
    xmlFile.parse<0>((*xFile).data());

    //Set the two nodes up
    initializeMainNode();
    initializeCurrentPage();

}


void Parser::getText() { bodyOfFile = currentPage->first_node("revision")->first_node("text"); }
void Parser::getTitle() { titleOfFile = currentPage->first_node("title"); }
void Parser::getNextPage() { currentPage = currentPage->next_sibling(); }
void Parser::getId() { idOfFile = currentPage->first_node("id"); }
void Parser::initializeCurrentPage() { currentPage = mainNode->first_node("page"); }
void Parser::initializeMainNode() { mainNode = xmlFile.first_node(); }
