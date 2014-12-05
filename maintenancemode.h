#ifndef MAINTENANCEMODE_H
#define MAINTENANCEMODE_H

#include "IndexInterface.h"
#include "documentindex.h"
#include "parser.h"
#include <iostream>
#include <windows.h>
#include "avltree.h"
#include <stdio.h>


#define EXIT_VALUE 0
#define MAX_MAINTENANCE_MODE_NUMBER 3
#define CREATE_DEFAULT_INDEX 1
#define ADD_TO_INDEX 2
#define CLEAR_CURRENT_INDEX 3

class MaintenanceMode
{
private:

    int argc;
    char** argv; 
    IndexInterface *dataStructure;
    DocumentIndex *documentIndexObject;
    Parser *parse;

    void createDefaultIndex();
    void addToIndex();
    void clearCurrentIndex();

    bool dataStructExists();
    void displayStructureExistsError();
    void display();
    void clearScreen();
    void pause();
    int getInput(int lowerBound, int upperBound);

    void destroyObjects();
    void setToNull();

    void errorHandle(int e);
public:
    MaintenanceMode(int consoleArgs, char** consolePaths);
    ~MaintenanceMode();

    void run();
};

#endif // MAINTENANCEMODE_H
