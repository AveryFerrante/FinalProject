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
        cin.ignore(1000, '\n'); // These clear cin so next loop will work
        while(cin.peek() != '\n')
        {
            cin >> tempUserInput;

            char *temp = new char[tempUserInput.length() + 1];
            strcpy(temp, tempUserInput.c_str());
            temp[tempUserInput.length()] = '\0';

            userQuery.push_back(temp);
        }

        if(strcmp(userQuery[0], "AND") == 0)
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

    for(size_t i = 0; i < userQuery.size(); ++i)
        delete [] userQuery[i];
}

void InteractiveMode::andQuery(vector<char *> &userQuery)
{
    if(userQuery.size() < 3) // Impossible to process
        throw USER_INPUT_UNDERFLOW;

    char *tempWord = stemAndPreserve(userQuery[1]); // no case where index 1 won't contain a search word
    vector<DocumentAndFrequency *> *word1 = dataStructure->getDocumentsForWord(tempWord);
    delete [] tempWord;

    tempWord = stemAndPreserve(userQuery[2]); // no case where index 2 won't contain a search word
    vector<DocumentAndFrequency *> *word2 = dataStructure->getDocumentsForWord(tempWord);
    delete [] tempWord;

    if(word1 == NULL || word2 == NULL)
        throw AND_WORD_DOES_NOT_EXIST;


    vector<DocumentAndFrequency *> *finalList = andProcessor(word1, word2);

    if(finalList->size() > 0)
    {
        string title("Results for ");
        title += userQuery[1];
        title += " AND ";
        title += userQuery[2];
        titlesAndBodies(finalList, title);
    }
    else
        throw NO_RESULTS;

    delete finalList;


}

vector<DocumentAndFrequency *>* InteractiveMode::andProcessor(std::vector<DocumentAndFrequency *> *list1, std::vector<DocumentAndFrequency *> *list2)
{
    // MUST BE SORTED ASCEDINGLY BY DOCUMENT ID VALUE
    vector<DocumentAndFrequency *> *returnVector = new vector<DocumentAndFrequency *>(list1->size() + list2->size());
    vector<DocumentAndFrequency *>::iterator it;

    it = set_intersection(list1->begin(), list1->end(), list2->begin(), list2->end(), returnVector->begin(), DocumentAndFrequency::andCompare);
    returnVector->resize(it - returnVector->begin());
    return returnVector;
}

void InteractiveMode::orQuery()
{

}

void InteractiveMode::singleQuery(vector<char *> &userQuery)
{
    clearScreen();
    vector<DocumentAndFrequency *> *documentList = NULL;

    if(userQuery.size() < 1)
        throw USER_INPUT_UNDERFLOW;

    char *tempWord = stemAndPreserve(userQuery[0]); // Word should ALWAYS be at index 0
    documentList = dataStructure->getDocumentsForWord(tempWord);
    delete [] tempWord;

    if(documentList == NULL)
        throw NO_RESULTS;

    else if(userQuery.size() > 1) // NOT words
    {
        if(strcmp(userQuery[1], "NOT") != 0)
            throw INCORRECT_FORMAT;

        vector<DocumentAndFrequency *> *finalList = notProcessor(userQuery, documentList);

        if(finalList->size() > 0)
        {
            std::string title("Results for ");
            title += userQuery[0];
            title += " NOT ";
            title += userQuery[userQuery.size() - 1];


            titlesAndBodies(finalList, title);
            delete finalList;
        }
        else
        {
            delete finalList;
            throw NO_RESULTS;
        }

    }
    else
    {
        string title("Results for ");
        title += userQuery[0];
        titlesAndBodies(documentList, title);
    }

}

std::vector<DocumentAndFrequency *> *InteractiveMode::notProcessor(vector<char *> &userQuery, std::vector<DocumentAndFrequency *> *goodWordList)
{
    if(userQuery.size() < 3)
        throw INCORRECT_FORMAT;

    size_t index = 0; // This gets the starting index where the NOT list of words begins
    for(; index < userQuery.size(); ++index)
    {
        if(strcmp(userQuery[index], "NOT") == 0)
            break;
    }
    if(index == userQuery.size() - 1)
        throw INCORRECT_FORMAT;

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
        returnVector = new vector<DocumentAndFrequency *>(tempGoodWordList->size());
        temp = stemAndPreserve(userQuery[index]);
        badWordList = dataStructure->getDocumentsForWord(temp);
        delete [] temp;

        if(badWordList == NULL)
        {
            delete returnVector;
            delete tempGoodWordList;
            throw NOT_WORD_DOES_NOT_EXIST;
        }

        it = set_difference(tempGoodWordList->begin(), tempGoodWordList->end(), badWordList->begin(), badWordList->end(), returnVector->begin(), DocumentAndFrequency::notCompare);
        returnVector->resize(it - returnVector->begin());

        delete tempGoodWordList; // No longer need the old good word list, we now have new updated one
    }

    return returnVector;
}

void InteractiveMode::titlesAndBodies(std::vector<DocumentAndFrequency *> *documentList, string &title)
{
    assert( documentList != NULL );
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
            cout << " - " << ((*documentList)[i])->getFinalFreq() << " total keyword occurences." << endl;
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

void InteractiveMode::sortByFreq(std::vector<DocumentAndFrequency *> *documentList) { std::sort(documentList->begin(), documentList->end(), DocumentAndFrequency::descendingByFreq); }

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
        cout << "The data structure and/or the index is not initialized (see manual)" << endl;
    if(e == AND_WORD_DOES_NOT_EXIST)
        cout << "A word in your AND query does not exist in the current index." << endl;
    if(e == INCORRECT_FORMAT)
        cout << "Your query entry is not formatted properly.\nSee manual for details on formatting." << endl;
    if(e == NO_RESULTS)
        cout << "There are no documents in the index that meet all of the search criteria." << endl;
    else
        cout << "UNKNOW ERROR OCCURED" << endl;

    pause(); // "Press any key to continue"
}


void InteractiveMode::clearScreen() { system("cls"); }
void InteractiveMode::pause() { system("pause"); }
