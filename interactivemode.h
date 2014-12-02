#ifndef INTERACTIVEMODE_H
#define INTERACTIVEMODE_H
#include "parser.h"
#include "documentindex.h"
#include "IndexInterface.h"
#include "avltree.h"
#include <windows.h>

#define EXIT_VALUE 0
#define MAX_INTERACTIVE_MODE_NUMBER 2
#define LOAD_FROM_INDEX 1
#define BOOLEAN_QUERY 2

#define AVL_TREE 1
#define HASH_TABLE 2

#define USER_INPUT_OVERFLOW 1992
#define USER_INPUT_UNDERFLOW 1993
#define UNINITIALIZED_OBJECT_ERROR 12993

class InteractiveMode
{
private:
    int argc;
    char** argv;
    IndexInterface *dataStructure;
    DocumentIndex *documentIndexObject;
    Parser *parse;

    //Utility Functions
    void display();
    void clearScreen();
    void pause();

    void loadFromIndex();
    bool getDataStruct();

    void search();
    void andQuery(std::vector<char *> &userQuery);
    void orQuery();
    void singleQuery();

    int getInput(int lowerBound, int upperBound);

    void errorHandle(int e);
public:
    InteractiveMode(int consoleArgs, char **consolePaths);
    void run();
};

#endif // INTERACTIVEMODE_H
