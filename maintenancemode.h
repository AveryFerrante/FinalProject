#ifndef MAINTENANCEMODE_H
#define MAINTENANCEMODE_H

#include "IndexInterface.h"
#include "documentindex.h"
#include "parser.h"
#include <iostream>
#include "avltree.h"

#define CREATE_DEF_INDEX 1
#define EXIT_VALUE 0
class MaintenanceMode
{
private:
    int argc;
    char** argv;
    IndexInterface *dataStructure;
    DocumentIndex *documentIndexObject;
    Parser *parse;

    void createDefaultIndex();
    bool dataStructExists();
    void displayStructureExistsError();
public:
    MaintenanceMode(int &consoleNumb, char **&consoleTxt, IndexInterface *&dataStruct,
                    DocumentIndex *&documentIndexObj, Parser *&prs);
    ~MaintenanceMode();

    void display();
    void doAction(int decision);
};

#endif // MAINTENANCEMODE_H
