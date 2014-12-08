#include "stresstestmode.h"
using namespace std;

StressTestMode::StressTestMode(int consoleArgs, char** consolePaths)
    : InteractiveMode(consoleArgs, consolePaths) { parse = NULL; }

void StressTestMode::run()
{
    clearScreen();
    cout << "Enter the name of the command file: ";
    string fileName;
    cin >> fileName;

    try
    {
        ifstream inputFile(fileName.c_str());
        if(!inputFile.is_open())
            throw INPUT_FILE_OPEN_ERROR;

        string instruction;
        while(inputFile >> instruction)
        {
            if(instruction == "ld")
                loadCommand(inputFile);
            else if(instruction == "clr")
                cout << "Delete index instructions" << endl;

            else if(instruction == "prse")
                parseCommand(inputFile);
            else if(instruction == "qry")
                queryCommand(inputFile);
            else if(instruction == "add")
                addCommand(inputFile);
            else if(instruction == "del")
                delCommand();
            else
                throw UNFORMATTED_ERROR;
        }
    }
    catch(int e)
    {
        errorHandle(e);
    }
}








//***************************************************UTILITY FUNCTIONS******************************************
void StressTestMode::loadCommand(ifstream &inputFile)
{
    clearScreen();
    string instruction;
    inputFile >> instruction;
    try
    {
        if(instruction == "ht") // Load into hash table
        {
            chrono::time_point<std::chrono::system_clock> start, end;
            start = chrono::system_clock::now();
            loadFromIndex(HASH_TABLE);
            end = chrono::system_clock::now();
            chrono::duration<double> elapsed_seconds = end-start;
            cout << "Elapsed sorting time: " << elapsed_seconds.count() << endl;
        }
        else if(instruction == "avlt")
        {
            chrono::time_point<std::chrono::system_clock> start, end;
            start = chrono::system_clock::now();
            loadFromIndex(AVL_TREE);
            end = chrono::system_clock::now();
            chrono::duration<double> elapsed_seconds = end-start;
            cout << "Elapsed sorting time: " << elapsed_seconds.count() << endl;
        }
        else
            throw UNFORMATTED_ERROR;
    }
    catch(int e)
    {
        errorHandle(e);
    }
}

void StressTestMode::addCommand(ifstream &inputFile)
{
    clearScreen();
    try
    {
        vector<string> xmlFiles;
        while(inputFile.peek() != '\n')
        {
            string temp;
            inputFile >> temp;
            xmlFiles.push_back(temp);
        }

        cout << "Setting up original Index" << endl;
        bool dataStructCreate = false;
        if(dataStructure == NULL && documentIndexObject == NULL) // If the user has not loaded a structure yet, else, just use the structure already in use.
        {
            dataStructure = new HashTable;
            documentIndexObject = new DocumentIndex;
            dataStructCreate = true;
            documentIndexObject->buildFromIndex();
            dataStructure->buildFromIndex();
        }

        parse = new Parser(argv[argc - 1], documentIndexObject->size() - 1);
        for(size_t i = 0; i  < xmlFiles.size(); ++i)
        {
            cout << "Indexing " << xmlFiles[i] << "..." << endl;
            parse->parse((xmlFiles[i]).c_str(), *dataStructure);
            cout << xmlFiles[i] << " successfully added to the index." << endl;
        }

        parse->writeToFile(*documentIndexObject);
        dataStructure->writeOutIndex();
        documentIndexObject->writeOutIndex();

        if(dataStructCreate == true) // If the user already created a data struct, then we won't delete it. It will also have the new file added to it.
        {
            deleteObjects();
            setToNull();
            pause();
        }
        else
        {
            delete parse;
            parse = NULL;
            pause();
        }

    }
    catch(int e)
    {
        errorHandle(e);
    }
}

void StressTestMode::delCommand()
{
    clearScreen();
    remove(WORD_INDEX_FILE_PATH);
    remove(DOCUMNET_INDEX_FILE_PATH);
    remove(DOCUMENT_OUTPUT_FILE);
    cout << "Index Deleted Successfully" << endl;
    pause();
}

void StressTestMode::queryCommand(ifstream &inputFile)
{
    clearScreen();
    string temp;
    vector<char *> userQuery;
    try
    {
        if(dataStructure == NULL || documentIndexObject == NULL)
        {
            inputFile.ignore(10000, '\n'); // Move the stream pointer to the next line so I don't try to process the search terms as commands from this qry
            throw UNINITIALIZED_OBJECT_ERROR;
        }

        while(inputFile.peek() != '\n' && inputFile.peek() != -1) // Will sometimes = -1 if the searching is the last line in the command file so must check that too
        {
            inputFile >> temp;
            char *tempWord = new char[temp.length() + 1];
            strcpy(tempWord, temp.c_str());
            userQuery.push_back(tempWord);
        }

        if(strcmp(userQuery[0], "AND") == 0)
            andQuery(userQuery);

        else if(strcmp(userQuery[0], "OR") == 0)
            orQuery(userQuery);

        else
            singleQuery(userQuery);


        for(size_t i = 0; i < userQuery.size(); ++i)
            delete [] userQuery[i];
    }
    catch(int e)
    {
        for(size_t i = 0; i < userQuery.size(); ++i)
            delete [] userQuery[i];
        errorHandle(e);
    }
}

void StressTestMode::parseCommand(ifstream &inputFile)
{
    clearScreen();
    if(dataStructure != NULL || documentIndexObject != NULL)
        throw INITIALIZED_OBJECT_ERROR;

    dataStructure = new HashTable;
    parse = new Parser(argv[argc - 1]);
    documentIndexObject = new DocumentIndex;

    vector<string> xmlFiles;
    while(inputFile.peek() != '\n')
    {
        string temp;
        inputFile >> temp;
        xmlFiles.push_back(temp);
    }


    for(size_t i = 0; i < xmlFiles.size(); ++i)
    {
        cout << "Opening file " << xmlFiles[i] << " for indexing" << endl;
        parse->parse(xmlFiles[i].c_str(), *dataStructure);
    }

    parse->writeToFile(*documentIndexObject);
    dataStructure->writeOutIndex();
    documentIndexObject->writeOutIndex();

    deleteObjects();
    setToNull();
    cout << "Index created successfully." << endl;
    pause();
}

void StressTestMode::deleteObjects()
{
    InteractiveMode::deleteObjects();
    delete parse;
}

void StressTestMode::setToNull()
{
    InteractiveMode::setToNull();
    parse = NULL;
}


