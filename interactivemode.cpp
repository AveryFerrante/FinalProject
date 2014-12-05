#include "interactivemode.h"
using namespace std;

InteractiveMode::InteractiveMode(int consoleArgs, char **consolePaths)
{
    argc = consoleArgs;
    argv = consolePaths;

    dataStructure = NULL;
    documentIndexObject = NULL;
    parse = NULL;
}

void InteractiveMode::run()
{
    int decision = -1;
    while(decision != 0)
    {
        clearScreen();
        display();
        decision = getInput(EXIT_VALUE, MAX_INTERACTIVE_MODE_NUMBER);

        if(decision == LOAD_FROM_INDEX)
            loadFromIndex();
        else if(decision == BOOLEAN_QUERY)
            search();
    }
}










//***************************UTILITY FUNCTIONS**************************************************

void InteractiveMode::search()
{
    vector<char *> userQuery;
    string tempUserInput;
    clearScreen();

    try
    {
        if(dataStructure == NULL || documentIndexObject == NULL)
            throw UNINITIALIZED_OBJECT_ERROR;
        cout << "Enter boolean querey:" << endl;
        cin.clear();
        cin.ignore(10000, '\n'); // These clear cin so next loop will work
        while(cin.peek() != '\n')
        {
            cin >> tempUserInput;

            char *temp = new char[tempUserInput.length() + 1];
            strcpy(temp, tempUserInput.c_str());
            temp[tempUserInput.length()] = '\0';

            userQuery.push_back(temp);
        }

        if(userQuery.size() > 5) // This is a fundamental idea of the program
            throw USER_INPUT_OVERFLOW;
        else if(strcmp(userQuery[0], "AND") == 0)
            andQuery(userQuery);
        else if(strcmp(userQuery[0], "OR") == 0)
            orQuery();
        else
            singleQuery(userQuery);
    }
    catch(int e)
    {
        errorHandle(e);
    }
}

void InteractiveMode::andQuery(vector<char *> &userQuery)
{
    if(userQuery.size() < 3) // Impossible to process
        throw USER_INPUT_UNDERFLOW;

    vector<int> *word1 = NULL;
    vector<int> *word2 = NULL;

    char *tempWord = new char[strlen(userQuery[1]) + 1]; // no case where index 1 won't contain a search word
    stemAndPreserve(userQuery[1], tempWord);
    word1 = dataStructure->getDocumentsForWord(tempWord);
    delete [] tempWord;

    tempWord = new char[strlen(userQuery[2]) + 1]; // no case where index 2 won't contain a search word
    stemAndPreserve(userQuery[2], tempWord);
    word2 = dataStructure->getDocumentsForWord(tempWord);
    delete [] tempWord;

    if(word1 == NULL || word2 == NULL)
        throw AND_WORD_DOES_NOT_EXIST;

    cout << "Size of " << userQuery[1] << ": " << word1->size() << endl;
    cout << "Size of " << userQuery[2] << ": " << word2->size() << endl;
    pause();

    vector<int> *finalList = NULL;
    if(word1->size() < word2->size())
        finalList = compileFinalList(word1, word2, AND_MODE);
    else
        finalList = compileFinalList(word2, word1, AND_MODE);


    if(finalList->size() > 0)
    {
        string title("Results for ");
        title += userQuery[1];
        title += " AND ";
        title += userQuery[2];
        titlesAndBodies(finalList, title);
    }
    else
    {
        cout << "No documents meet all of the requirements set forth in the search" << endl;
        pause();
    }

    delete finalList;



    /*
     * THIS ASSUMES THE USER CAN INPUT MORE THAN 2 WORDS DURING THE AND QUERY. NOT SURE IF THIS IS ALLOWED
    vector<vector<int> *> documentList;
    vector<vector<int> *> frequencyList;
    vector<int> *tempFreq = NULL;


    for(int i = 1; ((i < userQuery.size()) && (strcmp(userQuery[i], "NOT") != 0)); ++i)
    {
        char *stemmedWord = new char[strlen(userQuery[i]) + 1];
        stemAndPreserve(userQuery[i], stemmedWord);

        documentList.push_back(dataStructure->getDocumentsForWord(stemmedWord, tempFreq));
        frequencyList.push_back(tempFreq);

        delete [] stemmedWord;
    }

    // This gets the word that has the least amount of results (all other words doc ID's must be within this words ID's for AND)
    int indexOfSmallest = 0;
    for(int outer = 0; outer < documentList.size(); ++outer)
    {
        if(documentList[outer] == NULL) // Don't mess with it if one of the words is null
            throw AND_WORD_DOES_NOT_EXIST;

        if((documentList[outer])->size() < (documentList[indexOfSmallest])->size())
            indexOfSmallest = outer;
    }
    */

}

vector<int> *InteractiveMode::compileFinalList(std::vector<int> *word1, std::vector<int> *word2, int mode)
{   
    vector<int> *returnVec = new vector<int>();

    if(mode == AND_MODE)
    {
        assert ( word1->size() <= word2->size() );
        int inputCounter = 0;
        for(size_t i = 0; i < word1->size(); ++i) // word1 has smaller size
        {
            for(size_t x = 0; x < word2->size(); ++x)
            {
                if((*word1)[i] == (*word2)[x])
                {
                    ++inputCounter;
                    returnVec->push_back((*word1)[i]);
                }
            }

            if(inputCounter == MAX_RESULTS)
                break; // Only need to worry about the results that will be displayed
        }
    }

    else if(mode == NOT_MODE) // word1 (outer for loop) should be the list containing the docs of the actual words, word2 contains the not word list)
    {
        bool exists = false;
        for(size_t i = 0; i < word1->size(); ++i)
        {
            for(size_t x = 0; x < word2->size(); ++x)
            {
                if((*word1)[i] == (*word2)[x])
                {
                    exists = true;
                    break;
                }
            }

            if(!exists)
                returnVec->push_back((*word1)[i]);
            if(i == MAX_RESULTS)
                break;
            exists = false;
        }
    }

    return returnVec;
}

void InteractiveMode::orQuery()
{

}

void InteractiveMode::singleQuery(vector<char *> &userQuery)
{
    clearScreen();
    vector<int> *documentList = NULL;

    if(userQuery.size() < 1)
        throw USER_INPUT_UNDERFLOW;

    char *tempWord = new char[strlen(userQuery[0]) + 1];
    stemAndPreserve(userQuery[0], tempWord); // Word should ALWAYS be at index 0
    documentList = dataStructure->getDocumentsForWord(tempWord);
    delete [] tempWord;

    if(documentList == NULL)
    {
        cout << userQuery[0] << " does not exist in the current index." << endl;
        pause();
    }
    else if(userQuery.size() == 3) // Contains a NOT directive
    {
        vector<int> *finalList = notProcessor(userQuery, documentList);

        if(finalList == NULL) // NOT word did not exist
        {
            cout << "happy" << endl;
            cout << "No documents contained the word: " << userQuery[userQuery.size() - 1] << "." << endl;
            cout << "Displaying results for " << userQuery[0] << endl;
            string title("Results for ");
            title += userQuery[0];
            titlesAndBodies(documentList, title);
        }
        else if(finalList->size() > 0)
        {
            string title("Results for ");
            title += userQuery[0];
            title += " NOT ";
            title += userQuery[userQuery.size() - 1];
            titlesAndBodies(finalList, title);
        }
        else
        {
            cout << "No document meets all requirements set forth in the search" << endl;
            pause();
        }

        delete finalList;
    }
    else
    {
        string title("Results for ");
        title += userQuery[0];
        titlesAndBodies(documentList, title);
    }

}

std::vector<int> *InteractiveMode::notProcessor(std::vector<char *> &userQuery, std::vector<int> *currentDocumentList)
{
    if(userQuery.size() < 3)
        throw USER_INPUT_UNDERFLOW;

    if(strcmp(userQuery[userQuery.size() - 2], "NOT") == 0 && userQuery[userQuery.size() - 1])
    {
        char *tempWord = new char[strlen(userQuery[userQuery.size() - 1]) + 1];
        stemAndPreserve(userQuery[userQuery.size() - 1], tempWord);
        vector<int> *notWordList = dataStructure->getDocumentsForWord(tempWord);
        delete [] tempWord;

        if(notWordList != NULL)
            return compileFinalList(currentDocumentList, notWordList, NOT_MODE);
        else
            return NULL;
    }
    else
        throw USER_INPUT_UNDERFLOW;
}

void InteractiveMode::titlesAndBodies(std::vector<int> *documentList, string &title)
{
    assert( documentList != NULL );
    int decision = -1;

    while(decision != 0)
    {
        clearScreen();
        cout << title << ": " << endl;
        cout << "Enter 0 to return" << endl;
        for(size_t i = 0; i < documentList->size(); ++i)
        {
            cout << i + 1 << ": ";
            documentIndexObject->getTitle((*documentList)[i]);
            cout << endl;
            if(i == MAX_RESULTS)
                break;
        }

        cout << "Enter the number of the document you would like to view: ";
        if(documentList->size() > MAX_RESULTS)
            decision = getInput(EXIT_VALUE, MAX_RESULTS + 1);
        else
            decision = getInput(EXIT_VALUE, documentList->size());

        if((decision - 1) > -1)
        {
            clearScreen();
            documentIndexObject->getDocument((*documentList)[decision - 1]);
            pause();
        }
    }


}

void InteractiveMode::loadFromIndex()
{
    clearScreen();
    bool avlTree = getDataStruct();
    try
    {
        clearScreen();
        if(avlTree)
        {
            cout << "Loading the AVL-Tree." << endl;
            dataStructure = new avltree;
            documentIndexObject = new DocumentIndex;

            dataStructure->buildFromIndex();
            documentIndexObject->buildFromIndex();
            cout << "Loaded Successfully" << endl;
            pause();
        }

        else
        {
            //Hash Table Logic
        }
    }
    catch(int e)
    {
        errorHandle(e);
    }

}

bool InteractiveMode::getDataStruct()
{
    clearScreen();
    cout << "Please select which data structure to load into:" << endl;
    cout << AVL_TREE << ". AVL-Tree" << endl;
    cout << HASH_TABLE << ". Hash Table" << endl;

    int decision = getInput(AVL_TREE, HASH_TABLE);

    if(decision == 1)
        return true;
    else
        return false;
}

void InteractiveMode::display()
{
    cout << "Interactive Mode:" << endl;
    cout << EXIT_VALUE << ". Exit" << endl;
    cout << LOAD_FROM_INDEX << ". Load from Index" << endl;
    cout << BOOLEAN_QUERY << ". Boolean Query Search" << endl;
}

int InteractiveMode::getInput(int lowerBound, int upperBound)
{
    assert ( lowerBound < upperBound );
    string returnValue;
    cin >> returnValue;

    bool validInput = false;
    while(true)
    {
        for(size_t i = 0; i < returnValue.length(); ++i)
        {
            if(!isdigit(returnValue.at(i)))
            {
                validInput = false;
                break;
            }

            validInput = true;
        }

        if(validInput && atoi(returnValue.c_str()) >= lowerBound && atoi(returnValue.c_str()) <= upperBound)
            break; // Loop over, good input

        cout << "Invalid input, please re-enter: ";
        cin.ignore(100, '\n');
        cin >> returnValue;
    }

    return atoi(returnValue.c_str());
}

void InteractiveMode::stemAndPreserve(const char *word, char *destination)
{
    strcpy(destination, word);
    destination[stemObj.stem(destination, 0, strlen(destination) - 1)] = '\0';
}

void InteractiveMode::errorHandle(int e)
{
    clearScreen();
    cout << "ERROR ENCOUNTERED" << endl;
    if(e == XML_FILE_OPEN_ERROR)
        cout << "Error opening the file entered.\nMake sure the file name is spelled correctly and"
             << " is in the proper working directory (See manual)." << endl;
    if(e == STOP_WORDS_FILE_OPEN_ERROR)
        cout << "Unable to open the file containing the stop words.\nMake sure this is provided as the"
             << " last command line argument (see manual)." << endl;
    if(e == ERROR_BUILDING_INDEX)
        cout << "Unable to build the structure. Please make sure an index file exists in the working directory.\n"
             << "If none exists, you may use maintenance mode to build the default index and try again (see manual)." << endl;
    if( e == ERROR_BUILDING_DOCUMENT_INDEX)
        cout << "Unable to build document index. Please make sure an index file exists in the working directory.\n"
             << "If none exists, you may use maintenance mode to build the default index and try again (see manual)." << endl;
    if(e == USER_INPUT_OVERFLOW)
        cout << "You have entered too many terms.\nMax possible term number that can be processed is 5." << endl;
    if(e == USER_INPUT_UNDERFLOW)
        cout << "Query didn't contain minimum amount of words.\nMake sure query is properly formatted (see manual)." << endl;
    if(e == UNINITIALIZED_OBJECT_ERROR)
        cout << "The data structure and/or the index is not initialized (see manual)" << endl;
    if(e == AND_WORD_DOES_NOT_EXIST)
        cout << "A word in your AND query does not exist in the current index." << endl;

    pause(); // "Press any key to continue"
}


void InteractiveMode::clearScreen() { system("cls"); }
void InteractiveMode::pause() { system("pause"); }
