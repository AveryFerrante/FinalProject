#include "parser.h"

using namespace rapidxml;
using namespace std;

Parser::Parser(char *stopWordList, int startingPlace)
{
    try
    {
        initializeStopWordList(stopWordList);
    }
    catch(...)
    {
        throw STOP_WORDS_FILE_OPEN_ERROR;
    }

    documentCount = startingPlace; // This is only set if I am adding to an already existing index
}

Parser::~Parser()
{
    cout << "Destroying Parser" << endl;
    for(size_t i = 0; i < stopWords.size(); ++i)
        delete [] stopWords[i];

    assert ( fileBodies.size() == fileTitles.size() );

    for(size_t i = 0; i < fileBodies.size(); ++i)
    {
        delete fileBodies[i];
        delete fileTitles[i];
    }
    cout << "Parser Destroyed" << endl;
}

void Parser::parse(const char *fileName, IndexInterface &dataStructure)
{
    try
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
    catch(...)
    {
        throw XML_FILE_OPEN_ERROR;
    }
}



void Parser::writeToFile(DocumentIndex &documentIndexObject)
{
    cout << "Writing index to file" << endl;
    ofstream *outputFile;
    if(documentIndexObject.size() == 0)
    {
        outputFile = new ofstream(DOCUMENT_OUTPUT_FILE, fstream::binary);
        documentIndexObject.addDoc(0);
    }
    else
        outputFile = new ofstream(DOCUMENT_OUTPUT_FILE, fstream::binary | fstream::app); // Append to the end of the document


    for(size_t i = 0; i < fileBodies.size(); ++i)
    {
        (*outputFile) << *fileTitles[i] << endl;
        (*outputFile) << *fileBodies[i] << endl;
        documentIndexObject.addDoc(outputFile->tellp());
    }
    outputFile->close();
    delete outputFile;
}


// ********************************UTILITY FUNCTIONS****************************************************************************
void Parser::initializeStopWordList(const char *fileName)
{
    ifstream wordList(fileName);
    char *buffer = new char[81];

    while(!wordList.eof())
    {
        wordList.getline(buffer, 80);
        char *temp = new char[strlen(buffer) + 1];
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

        if(!isalpha(word[i]) || !isprint((unsigned)(word[i])))
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
        if(strlen(bodyContents) >= 22 || isStopWord(bodyContents)) // Skip this word
        {
            bodyContents = ++whatsLeft; // Point to beginning of next word
            whatsLeft = strchr(bodyContents, ' ');
            continue;
        }

        bodyContents[stemObject.stem(bodyContents, 0, strlen(bodyContents) - 1)] = '\0';
        if(strlen(bodyContents) <= 1)
        {
            bodyContents = ++whatsLeft; // Point to beginning of next word
            whatsLeft = strchr(bodyContents, ' ');
            continue;
        }

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
    if(!dataStructure.alreadyContains(word, documentCount)) // This will update the frequency / documents if it is found
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
