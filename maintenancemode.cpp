#include "maintenancemode.h"
using namespace std;

MaintenanceMode::MaintenanceMode(int consoleArgs, char **consolePaths)
{
    argc = consoleArgs;
    argv = consolePaths;

    dataStructure = NULL;
    documentIndexObject = NULL;
    parse = NULL;
}
MaintenanceMode::~MaintenanceMode()
{
    destroyObjects();
}

void MaintenanceMode::run()
{
    int decision = -1;
    while(decision != 0)
    {
        display();
        decision = getInput(EXIT_VALUE, MAX_MAINTENANCE_MODE_NUMBER);

        if(decision == CREATE_DEFAULT_INDEX)
            createDefaultIndex();
        if(decision == ADD_TO_INDEX)
            addToIndex();
        if(decision == CLEAR_CURRENT_INDEX)
            clearCurrentIndex();
    }


}


//*******************************UTILITY FUNCTIONS**************************************************************
int MaintenanceMode::getInput(int lowerBound, int upperBound)
{
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

void MaintenanceMode::display()
{
    clearScreen();
    cout << "Maintenance Mode:" << endl;
    cout << EXIT_VALUE << ". Exit" << endl;
    cout << CREATE_DEFAULT_INDEX << ". Build Default Index" << endl;
    cout << ADD_TO_INDEX << ". Add File to Index" << endl;
    cout << CLEAR_CURRENT_INDEX << ". Delete Current Index" << endl;
}

void MaintenanceMode::clearCurrentIndex()
{
    clearScreen();
    remove(WORD_INDEX_FILE_PATH);
    remove(DOCUMNET_INDEX_FILE_PATH);
    cout << "Index Deleted Successfully" << endl;
    pause();
}

void MaintenanceMode::addToIndex()
{
    clearScreen();
    cout << "Please enter the file name: ";
    string fileName;
    cin >> fileName;
    try
    {
        cout << "Setting up original Index" << endl;
        dataStructure = new avltree;
        documentIndexObject = new DocumentIndex;
        parse = new Parser(argv[argc - 1]);

        dataStructure->buildFromIndex();
        documentIndexObject->buildFromIndex();

        cout << "Indexing " << fileName << endl;
        parse->parse(fileName.c_str(), *dataStructure);

        parse->writeToFile(*documentIndexObject);

        dataStructure->writeOutIndex();
        documentIndexObject->writeOutIndex();
        cout << fileName << " successfully added to the existing index." << endl;
        pause();
    }
    catch(int e)
    {
        errorHandle(e);
    }

    destroyObjects();
    setToNull();
}

void MaintenanceMode::createDefaultIndex()
{
    clearScreen();
    //assert ( argc > 2 ); // User must include stopWords list
    if(dataStructExists())
    {
        displayStructureExistsError();
        return;
    }

    dataStructure = new avltree;
    parse = new Parser(argv[argc - 1]);
    documentIndexObject = new DocumentIndex;
    for(int i = 1; i < argc - 1; ++i)
    {
        cout << "Opening file " << argv[i] << " for indexing" << endl;
        parse->parse(argv[i], *dataStructure);
    }

    parse->writeToFile(*documentIndexObject);
    dataStructure->writeOutIndex();
    documentIndexObject->writeOutIndex();
    //destroyObjects();
    setToNull();
    cout << "Index created successfully." << endl;
    pause();
}

void MaintenanceMode::errorHandle(int e)
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

    pause(); // "Press any key to continue"
}

void MaintenanceMode::destroyObjects()
{
    delete dataStructure;
    delete documentIndexObject;
    delete parse;
}

void MaintenanceMode::setToNull()
{
    dataStructure = NULL;
    documentIndexObject = NULL;
    parse = NULL;
}


bool MaintenanceMode::dataStructExists()
{
    if( documentIndexObject != NULL || dataStructure != NULL )
        return true;
    return false;
}

void MaintenanceMode::clearScreen() { system("cls"); }
void MaintenanceMode::pause() { system("pause"); }

void MaintenanceMode::displayStructureExistsError()
{ cout << "Error: A data structure is already contained in memory. Please remove structure from memory and try again." << endl; }
