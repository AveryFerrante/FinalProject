#include "stresstestmode.h"
using namespace std;

StressTestMode::StressTestMode(int consoleArgs, char** consolePaths)
    : InteractiveMode(consoleArgs, consolePaths) { }

void StressTestMode::run()
{
    cout << "Enter the name of the command file: ";
    string fileName;
    cin >> fileName;

    try
    {
        ifstream inputFile(fileName.c_str());
        if(!inputFile.is_open())
            throw INPUT_FILE_OPEN_ERROR;

        string instruction;
        while(!inputFile.eof())
        {
           inputFile >> instruction;

           if(instruction == "ld")
               loadCommand(inputFile);

           else if(instruction == "clr")
               cout << "Delete index instructions" << endl;

           else if(instruction == "prse")
               parseCommand(inputFile);

           else if(instruction == "qry")
               cout << "Query instructions" << endl;

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
    string instruction;
    inputFile >> instruction;

    cout << "Processing " << instruction << endl;
    if(instruction == "ht") // Load into hash table
        loadFromIndex(HASH_TABLE);
    else if(instruction == "avlt")
        loadFromIndex(AVL_TREE);
    else
        throw UNFORMATTED_ERROR;
}

void StressTestMode::parseCommand(ifstream &inputFile)
{
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
    delete parse;
    delete dataStructure;
    delete documentIndexObject;
}


