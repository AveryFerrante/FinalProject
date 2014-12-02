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
            singleQuery();
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

    vector<vector<int> *> documentList;
    vector<int> *tempFreqList;
    vector<vector<int> *> frequencyList;
    for(size_t i = 1; ((i < userQuery.size()) && (strcmp(userQuery[i], "NOT") != 0)); ++i)
    {
        documentList.push_back(dataStructure->getDocumentsForWord(userQuery[i], tempFreqList));
        frequencyList.push_back(tempFreqList);
    }

}

void InteractiveMode::orQuery()
{

}

void InteractiveMode::singleQuery()
{

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
    while(!validInput)
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
        cin >> returnValue;
    }

    return atoi(returnValue.c_str());
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
        cout << "Cannot have a boolean query with less than 3 words.\nMake sure query is properly formatted (see manual)." << endl;

    pause(); // "Press any key to continue"
}


void InteractiveMode::clearScreen() { system("cls"); }
void InteractiveMode::pause() { system("pause"); }
