#include "searchengine.h"

using namespace std;

SearchEngine::SearchEngine(int numb, char **words)
{
    parse = NULL;
    documentIndexObject = NULL;
    dataStructure = NULL;

    argc = numb;
    argv = words;
}

void SearchEngine::runEngine()
{
    displayWelcome();
    int decision = getInput(EXIT_VALUE, MAX_MODE_NUMBER);

    while(decision != 0)
    {
        switch(decision)
        {
        case 0 : break;
        case 1 :
        {
            MaintenanceMode currentMode(argc, argv, dataStructure, documentIndexObject, parse);
            clearScreen();
            while(decision != 0)
            {
                currentMode.display();
                decision = getInput(EXIT_VALUE, MAX_MAINTENANCE_MODE_NUMBER);
                currentMode.doAction(decision);
            }
            break;
        }
        case 2 : // User Mode
            clearScreen();
            while(decision != 0)
            {
                displayUserMode();
                decision = getInput(EXIT_VALUE, MAX_USER_MODE_NUMBER);

                switch(decision)
                {
                case 0 : break;
                case 1 : // Build default index

                    break;
                case 2 : // Build from index
                    clearScreen();
                    buildFromIndex();
                    break;
                }
            }

        case 3 : break; // Stress Test Mode
        }

        clearScreen();
        displayWelcome();
        decision = getInput(EXIT_VALUE, MAX_MODE_NUMBER);
    }

    // Last test things here ( did u save, etc. )
}























//**************************UTILITY FUNCTIONS***********************************//
int SearchEngine::getInput(int lowerBound, int upperBound)
{
    string returnValue;
    cin >> returnValue;

    bool validInput = false;
    while(!validInput)
    {
        for(int i = 0; i < returnValue.length(); ++i)
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

void SearchEngine::buildFromIndex()
{
    if(dataStrcutExists())
    {
        //displayStructureExistsError();
        return;
    }

    ifstream inputFile("wordindex.jaf");
    ifstream inputFile1("documentindex.jaf");
    if(inputFile.is_open() && inputFile1.is_open())
    {
        dataStructure = new avltree;
        dataStructure->buildFromIndex(inputFile);

        documentIndexObject = new DocumentIndex;
        documentIndexObject->buildFromIndex(inputFile1);

        cout << "Build successful." << endl;
    }
    else if(!inputFile.is_open())
        displayCannotFindFileError("wordindex.jaf");
    else
        displayCannotFindFileError("documentindex.jaf");

    inputFile.close();
    inputFile1.close();
}

void SearchEngine::displayWelcome()
{
    cout << "Welcome to the WikiMedia search engine. *Enter 0 at anytime during the program "
         " to return here*\n" << endl;
    cout << "Please select one of the options below:" << endl;
    cout << "0. Exit Program\n1. Maintenance Mode\n2. User Mode\n3. Stress Test Mode" << endl;
}

void SearchEngine::displayUserMode()
{
    cout << "User Mode:" << endl;
    cout << "0. Return to Previous Screen\n1. Build Default Index\n2. Build from Index" << endl;
}

bool SearchEngine::dataStrcutExists()
{
    if( documentIndexObject != NULL || dataStructure != NULL )
        return true;
    return false;
}

void SearchEngine::clearScreen() { system("cls"); }
void SearchEngine::displayCannotFindFileError(string fileName)
{
    cout << "Error opening file: " << fileName << "." << endl;
    cout << "Please make sure file exists in the working directory." << endl;
}
