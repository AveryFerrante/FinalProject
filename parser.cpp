#include "parser.h"

using namespace rapidxml;
using namespace std;

Parser::Parser(char *xmlFileName, char *stopWordList)
{
    xFile = new file<>(xmlFileName);
    xmlFile.parse<0>((*xFile).data());

    //Set the two nodes up
    initializeMainNode();
    initializeCurrentPage();
    getPageInfo();

    initializeStopWordList(stopWordList);
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

        *whatsLeft = '\0';

        if(strlen(bodyContents) > 22 || isStopWord(bodyContents)) // Skip this word
        {
            bodyContents = ++whatsLeft; // Point to beginning of next word
            whatsLeft = strchr(bodyContents, ' ');
            continue;
        }

        cout << "On word: " << bodyContents << endl;
        removeNonAlphaCharacters(bodyContents);
        cout << "After removing characters: " << bodyContents << endl;
        //bodyContents[stem(bodyContents, 0, strlen(bodyContents) - 1)] = '\0';


        bodyContents = ++whatsLeft; // Point to beginning of next word
        whatsLeft = strchr(bodyContents, ' ');
    }
    cout << "Exited while loop " << endl;
}

void Parser::parse()
{
    int docCounter = 0;
    while(currentPage != NULL)
    {
        getPageInfo();
        cout << "Got page info" << endl;
        if(bodyOfFile->value_size() < 100)
        {
            cout << "Less than 100" << endl;
            getNextPage();
            continue;
        }
        if (docCounter == 1) cout << "Debug" << endl;
        writeDataToVectors();
        cout << "Wrote data to vectors." << endl;
        cleanBodyContents();
        getNextPage();
        cout << "Got the next page" << endl;
        ++docCounter;
    }
    cout << "Kept " << docCounter << " documents." << endl;
    ofstream outputFile("file.txt", ios::binary);
    fileStartPosition.push_back(seekPosition); // Give a 0 for starting
    for(int i = 0; i < fileBodies.size(); ++i)
    {
        outputFile << fileTitles[i] << endl;
        outputFile << fileBodies[i] << endl;
        fileStartPosition.push_back(outputFile.tellp());
    }
    fileStartPosition.push_back(outputFile.tellp());
    outputFile.close();

}

void Parser::getFile(int index)
{
    ifstream outputFile("file.txt", ios::binary);
    int length = fileStartPosition[index + 1] - fileStartPosition[index];
    char *word = new char[length];
    outputFile.seekg(fileStartPosition[index]);
    outputFile.read(word, length);
    word[length] = '\0';
    cout << word << endl;

}


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






// **********UTILITY FUNCTIONS****************************************************************************
void Parser::removeNonAlphaCharacters(char *&word)
{
    for(size_t i = 0; i < strlen(word); ++i)
    {
        word[i] = tolower(word[i]);

        if(!isalpha(word[i]))
            *(std::remove(word, word + strlen(word), word[i--])) = 0;
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

void Parser::writeDataToVectors()
{
    fileBodies.push_back(string(bodyOfFile->value()));
    fileTitles.push_back(string(titleOfFile->value()));
}

void Parser::getPageInfo() // Just a function for testing the class, not needed
{
    getTitle();
    getId();
    getText();
}


void Parser::getText() { bodyOfFile = currentPage->first_node("revision")->first_node("text"); }
void Parser::getTitle() { titleOfFile = currentPage->first_node("title"); }
void Parser::getNextPage() { currentPage = currentPage->next_sibling(); }
void Parser::getId() { idOfFile = currentPage->first_node("id"); }
void Parser::initializeCurrentPage() { currentPage = mainNode->first_node("page"); }
void Parser::initializeMainNode() { mainNode = xmlFile.first_node(); }
