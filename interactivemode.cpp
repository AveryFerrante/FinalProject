#include "interactivemode.h"
using namespace std;

InteractiveMode::InteractiveMode(int consoleArgs, char **consolePaths)
{
    argc = consoleArgs;
    argv = consolePaths;

    setToNull(); // Sets the member variable pointers to null
}

InteractiveMode::~InteractiveMode() { deleteObjects(); }

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
        else if(decision == DELETE_CURRENT_INDEX)
            deleteCurrentIndex();
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
        cin.ignore(1000, '\n'); // These clear cin so the following loop will work
        while(cin.peek() != '\n')
        {
            cin >> tempUserInput;

            char *temp = new char[tempUserInput.length() + 1];
            strcpy(temp, tempUserInput.c_str());

            userQuery.push_back(temp);
        }

        if(strcmp(userQuery[0], "AND") == 0)
            andQuery(userQuery);

        else if(strcmp(userQuery[0], "OR") == 0)
            orQuery(userQuery);

        else
            singleQuery(userQuery);
    }
    catch(int e)
    {
        errorHandle(e);
    }

    for(size_t i = 0; i < userQuery.size(); ++i)
        delete [] userQuery[i];
}

void InteractiveMode::andQuery(vector<char *> &userQuery)
{
    if(userQuery.size() < 3) // Impossible to process
        throw USER_INPUT_UNDERFLOW;

    vector<DocumentAndFrequency *> *finalList = andProcessor(userQuery);
    finalList = notProcessor(userQuery, finalList);

    if(finalList->size() > 0)
    {
        string title = createTitle(userQuery);
        titlesAndBodies(finalList, title);
    }
    else
        throw NO_RESULTS;

    delete finalList;
}

void InteractiveMode::orQuery(vector<char *> &userQuery)
{
    if(userQuery.size() < 3)
        throw USER_INPUT_UNDERFLOW;

    vector<DocumentAndFrequency *> *finalList = new vector<DocumentAndFrequency *>();
    for(size_t index = 1; index < userQuery.size() && strcmp(userQuery[index], "NOT") != 0; ++index)
    {
        char *tempWord = stemAndPreserve(userQuery[index]);
        vector<DocumentAndFrequency *> *temp = dataStructure->getDocumentsForWord(tempWord);
        delete [] tempWord;

        finalList->insert(finalList->end(), temp->begin(), temp->end());
    }

    finalList = notProcessor(userQuery, finalList);

    if(finalList->size() > 0)
    {
        string title = createTitle(userQuery);
        titlesAndBodies(finalList, title);
        delete finalList;
    }
    else
    {
        delete finalList;
        throw NO_RESULTS;
    }
}

void InteractiveMode::singleQuery(vector<char *> &userQuery)
{
    if(userQuery.size() < 1)
        throw USER_INPUT_UNDERFLOW;

    char *tempWord = stemAndPreserve(userQuery[0]); // Word should ALWAYS be at index 0
    vector<DocumentAndFrequency *> *documentList = dataStructure->getDocumentsForWord(tempWord);
    delete [] tempWord;

    if(documentList == NULL)
        throw NO_RESULTS;

    else if(userQuery.size() > 1) // NOT words
    {
        if(strcmp(userQuery[1], "NOT") != 0)
            throw INCORRECT_FORMAT;

        documentList = notProcessor(userQuery, documentList);

        if(documentList->size() > 0)
        {
            string title = createTitle(userQuery);
            titlesAndBodies(documentList, title);
            delete documentList;
        }
        else
        {
            delete documentList;
            throw NO_RESULTS;
        }

    }
    else
    {
        string title = createTitle(userQuery);
        titlesAndBodies(documentList, title);
    }

}

vector<DocumentAndFrequency *>* InteractiveMode::andProcessor(vector<char *> &userQuery)
{
    char *tempWord = stemAndPreserve(userQuery[1]); // no case where index 1 won't contain a search word
    vector<DocumentAndFrequency *> *list1 = dataStructure->getDocumentsForWord(tempWord);
    delete [] tempWord;

    tempWord = stemAndPreserve(userQuery[2]); // no case where index 2 won't contain a search word
    vector<DocumentAndFrequency *> *list2 = dataStructure->getDocumentsForWord(tempWord);
    delete [] tempWord;

    if(list1 == NULL || list2 == NULL)
        throw AND_WORD_DOES_NOT_EXIST;

    // MUST BE SORTED ASCEDINGLY BY DOCUMENT ID VALUE

    // This vector should never be as big as I declare it here, but it is resized later, so I am being safe here.
    vector<DocumentAndFrequency *> *returnVector = new vector<DocumentAndFrequency *>(list1->size() + list2->size());
    vector<DocumentAndFrequency *>::iterator it;

    it = set_intersection(list1->begin(), list1->end(), list2->begin(), list2->end(), returnVector->begin(), DocumentAndFrequency::andCompare);
    returnVector->resize(it - returnVector->begin());


    // Start at 3 because we have already processed the first two AND words. Now we see if we should process more.
    for(size_t index = 3; index < userQuery.size() && strcmp(userQuery[index], "NOT") != 0; ++index)
    {
        list1 = returnVector; // This is now one of our "good word lists."
        char *temp = stemAndPreserve(userQuery[index]);
        list2 = dataStructure->getDocumentsForWord(temp);
        delete [] temp;

        if(list2 == NULL)
        {
            delete list1;
            throw AND_WORD_DOES_NOT_EXIST;
        }

        returnVector = new vector<DocumentAndFrequency *>(list1->size() + list2->size());
        it = set_intersection(list1->begin(), list1->end(), list2->begin(), list2->end(), returnVector->begin(), DocumentAndFrequency::andCompare);
        returnVector->resize(it - returnVector->begin()); // This is now our list that is meeting all the AND requirements

        delete list1; // No longer need the old good word list, returnVector is our new good word list.

    }


    return returnVector;
}

std::vector<DocumentAndFrequency *> *InteractiveMode::notProcessor(vector<char *> &userQuery, std::vector<DocumentAndFrequency *> *goodWordList)
{
    if(userQuery.size() < 3)
        throw INCORRECT_FORMAT;

    size_t index = 0; // This gets the starting index where the NOT list of words begins
    for(; index < userQuery.size() && strcmp(userQuery[index], "NOT") != 0; ++index);

    if(index == userQuery.size())
    {
        return goodWordList; // Does not have any NOT words to process
    }
    ++index; // Now pointing at the next not word.


    // MUST BE SORTED ASCENDINGLY BY DOCUMENT ID NUMBER!
    vector<DocumentAndFrequency *> *returnVector = new vector<DocumentAndFrequency *>(goodWordList->size());
    vector<DocumentAndFrequency *>::iterator it;

    char *temp = stemAndPreserve(userQuery[index++]);
    vector<DocumentAndFrequency *> *badWordList = dataStructure->getDocumentsForWord(temp);
    delete [] temp;

    if(badWordList == NULL)
    {
        delete returnVector;
        throw NOT_WORD_DOES_NOT_EXIST;
    }

    it = set_difference(goodWordList->begin(), goodWordList->end(), badWordList->begin(), badWordList->end(), returnVector->begin(), DocumentAndFrequency::notCompare);
    returnVector->resize(it - returnVector->begin());
    // Initialization complete. Continue Processing


    for(; index < userQuery.size(); ++index)
    {
        vector<DocumentAndFrequency *> *tempGoodWordList = returnVector; // This is now the "good word list". Must use it in the set algorithm
        temp = stemAndPreserve(userQuery[index]);
        badWordList = dataStructure->getDocumentsForWord(temp);
        delete [] temp;

        if(badWordList == NULL)
        {
            delete tempGoodWordList;
            throw NOT_WORD_DOES_NOT_EXIST;
        }

        returnVector = new vector<DocumentAndFrequency *>(tempGoodWordList->size());
        it = set_difference(tempGoodWordList->begin(), tempGoodWordList->end(), badWordList->begin(), badWordList->end(), returnVector->begin(), DocumentAndFrequency::notCompare);
        returnVector->resize(it - returnVector->begin());

        delete tempGoodWordList; // No longer need the old good word list, we now have new updated one
    }

    return returnVector;
}

void InteractiveMode::titlesAndBodies(std::vector<DocumentAndFrequency *> *documentList, string &title)
{
    assert( documentList != NULL ); // Really this will never happen, but defensive programming
    int decision = -1;

    sortByFreq(documentList);
    while(decision != 0)
    {
        clearScreen();
        cout << title << ": " << endl;
        cout << "Enter 0 to return" << endl;
        for(size_t i = 0; i < documentList->size(); ++i)
        {
            cout << i + 1 << ": ";
            documentIndexObject->getTitle(((*documentList)[i])->getDocNumb());
            cout << " - " << ((*documentList)[i])->getFinalFreq() << " occurances of a keyword." << endl;
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
            documentIndexObject->getDocument(((*documentList)[decision - 1])->getDocNumb());
            pause();
        }
    }

    for(size_t i = 0; i < documentList->size(); ++i)
        (*documentList)[i]->resetFreq(); // Set the final frequencies back to original value so they are not permanently altered for future searches

}

string InteractiveMode::createTitle(std::vector<char *> &userQuery)
{
    // Some redundant looking practices. What I came up with that worked in under 10 minutes
    string returnVal("Results for ");
    size_t index = 0;
    if(strcmp(userQuery[index], "AND") == 0)
    {
        for(index = 1; index < userQuery.size() && strcmp(userQuery[index], "NOT") != 0; ++index)
        {
            returnVal += userQuery[index]; returnVal += " ";
            if((index + 1) < userQuery.size() && strcmp(userQuery[index + 1], "NOT") != 0)
                returnVal += "AND "; // Don't want to add this if no word is coming after it, thats why the above check happens
        }
    }
    else if(strcmp(userQuery[index], "OR") == 0)
    {
        for(index = 1; index < userQuery.size() && strcmp(userQuery[index], "NOT") != 0; ++index)
        {
            returnVal += userQuery[index]; returnVal += " ";
            if((index + 1) < userQuery.size() && strcmp(userQuery[index + 1], "NOT") != 0)
                returnVal += "OR ";
        }
    }
    else // Single word query
    {
        returnVal += userQuery[index++]; returnVal += " ";
    }

    // NOT words
    if(index < userQuery.size() && strcmp(userQuery[(index)++], "NOT") == 0)
    {
        returnVal += "NOT ";
        for(; index < userQuery.size(); ++index)
        {
            returnVal += userQuery[index]; returnVal += " ";
        }
    }

    return returnVal;
}

void InteractiveMode::sortByFreq(std::vector<DocumentAndFrequency *> *documentList) { std::sort(documentList->begin(), documentList->end(), DocumentAndFrequency::descendingByFreq); }

void InteractiveMode::deleteCurrentIndex()
{
    try
    {
        if(dataStructure == NULL || documentIndexObject == NULL)
            throw UNINITIALIZED_OBJECT_ERROR;

        clearScreen();
        deleteObjects();
        setToNull();
        pause();
    }
    catch(int e)
    {
        errorHandle(e);
    }
}

void InteractiveMode::loadFromIndex(int structure /* = 0*/) // Structure is passed from stress test mode
{
    try
    {
        if(dataStructure != NULL || documentIndexObject != NULL)
            throw INITIALIZED_OBJECT_ERROR;

        bool avlTree;
        if(structure == 0) // Building from interactive mode
            avlTree = getDataStruct();
        else // Building from stress test mode
        {
            if(structure == AVL_TREE)
                avlTree = true;
            else
                avlTree = false;
        }

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
            cout << "Loading the Hash Table." << endl;
            dataStructure = new HashTable;
            documentIndexObject = new DocumentIndex;

            dataStructure->buildFromIndex();
            documentIndexObject->buildFromIndex();
            cout << "Loaded Successfully" << endl;
            pause();
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

    if(decision == AVL_TREE)
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
    cout << DELETE_CURRENT_INDEX << ". Delete the Current Data Structure." << endl;
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

char * InteractiveMode::stemAndPreserve(const char *word)
{
    char *temp = new char[strlen(word) + 1];
    strcpy(temp, word);
    temp[strlen(word)] = '\0';
    temp[stemObj.stem(temp, 0, strlen(temp) - 1)] = '\0';
    return temp;
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
        cout << "Cannot perform task because the current data structure is not initialized (see manual)" << endl;
    if(e == AND_WORD_DOES_NOT_EXIST)
        cout << "A word in your AND query does not exist in the current index." << endl;
    if(e == INCORRECT_FORMAT)
        cout << "Your query entry is not formatted properly.\nSee manual for details on formatting." << endl;
    if(e == NO_RESULTS)
        cout << "There are no documents in the index that meet all of the search criteria." << endl;
    if(e == INITIALIZED_OBJECT_ERROR)
        cout << "There is already a data strucutre loaded in memory." << endl;
    if(e == INPUT_FILE_OPEN_ERROR)
        cout << "Could not open the file entered by the user (see manual)" << endl;
    if(e == UNFORMATTED_ERROR)
        cout << "Unknown commaned encountered. Improper file formatting (see manual)." << endl;

    pause(); // "Press any key to continue"
}

void InteractiveMode::deleteObjects()
{
    delete documentIndexObject;
    delete dataStructure;
}

void InteractiveMode::setToNull()
{
    documentIndexObject = NULL;
    dataStructure = NULL;
}


void InteractiveMode::clearScreen() { system("cls"); }
void InteractiveMode::pause() { system("pause"); }
