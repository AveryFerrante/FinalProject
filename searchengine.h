#ifndef SEARCHENGINE_H
#define SEARCHENGINE_H
#include "parser.h"
#include "documentindex.h"
#include "avltree.h"
#include <stdlib.h>
#include "maintenancemode.h"



#define MAX_MODE_NUMBER 3
#define MAX_USER_MODE_NUMBER 2
#define MAX_MAINTENANCE_MODE_NUMBER 1


class SearchEngine
{
private:
    // Member Variables
    Parser *parse;
    DocumentIndex *documentIndexObject;
    IndexInterface *dataStructure;
    // Console variables
    int argc;
    char** argv;


    void createDefaultIndex(); // These will be the xml files this class is to parse / index
    void buildFromIndex();
    void displayWelcome();
    void displayUserMode();
    void clearScreen();

    int getInput(int, int);
    bool dataStrcutExists();

    void displayStructureExistsError();
    void displayCannotFindFileError(std::string); // Prints file name
public:
    SearchEngine(int, char**);

    void runEngine(); // Driver function

};

#endif // SEARCHENGINE_H
