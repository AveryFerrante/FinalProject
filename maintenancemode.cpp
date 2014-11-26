#include "maintenancemode.h"
using namespace std;

MaintenanceMode::MaintenanceMode(int &consoleNumb, char** &consoleTxt,
                                 IndexInterface *&dataStruct, DocumentIndex *&documentIndexObj, Parser *&prs)
{
    argc = consoleNumb;
    argv = consoleTxt;

    dataStructure = dataStruct;
    documentIndexObject = documentIndexObj;
    parse = prs;
}
MaintenanceMode::~MaintenanceMode()
{
    delete [] dataStructure;
    dataStructure = NULL;
    delete [] documentIndexObject;
    documentIndexObject = NULL;
    delete[] parse;
    parse = NULL;
}

void MaintenanceMode::display()
{
    cout << "Maintenance Mode:" << endl;
    cout << "0. Return to Previous Screen\n1. Build default Index" << endl;
}

void MaintenanceMode::doAction(int decision)
{
    if(decision == EXIT_VALUE)
        return;
    if(decision == CREATE_DEF_INDEX)
        createDefaultIndex();

}

void MaintenanceMode::createDefaultIndex()
{
    assert ( argc > 2 ); // User must include stopWords list
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
    cout << "Index created successfully." << endl;
}


bool MaintenanceMode::dataStructExists()
{
    if( documentIndexObject != NULL || dataStructure != NULL )
        return true;
    return false;
}

void MaintenanceMode::displayStructureExistsError()
{ cout << "Error: A data structure is already contained in memory. Please remove structure from memory and try again." << endl; }
