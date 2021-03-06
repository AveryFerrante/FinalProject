#ifndef INTERACTIVEMODE_H
#define INTERACTIVEMODE_H
#include "parser.h"
#include "documentindex.h"
#include "IndexInterface.h"
#include "avltree.h"
#include "hashtable.h"
#include <windows.h>

#define EXIT_VALUE 0
#define MAX_INTERACTIVE_MODE_NUMBER 2
#define LOAD_FROM_INDEX 1
//#define DELETE_CURRENT_INDEX 3
#define BOOLEAN_QUERY 2

#define AVL_TREE 1
#define HASH_TABLE 2

#define USER_INPUT_OVERFLOW 1992
#define USER_INPUT_UNDERFLOW 1993
#define UNINITIALIZED_OBJECT_ERROR 12993
#define INITIALIZED_OBJECT_ERROR 388392
#define AND_WORD_DOES_NOT_EXIST 84383
#define NOT_WORD_DOES_NOT_EXIST 7875
#define INCORRECT_FORMAT 1584
#define NO_RESULTS 44747

#define INPUT_FILE_OPEN_ERROR 1234321 // These are errors for stress test mode
#define UNFORMATTED_ERROR 838383



class InteractiveMode
{
protected: // Stress Test Mode inherits from this so all of these are protected
    int argc;
    char** argv;
    IndexInterface *dataStructure;
    DocumentIndex *documentIndexObject;
    Stemmer2 stemObj;

    //Utility Functions
    void display();
    void clearScreen();
    void pause();

    void loadFromIndex(int structure = 0);
    bool getDataStruct();
    void search();
    //void deleteCurrentIndex();

    void andQuery(std::vector<char *> &userQuery);
    void orQuery(std::vector<char *> &userQuery);
    void singleQuery(std::vector<char *> &userQuery);

    void titlesAndBodies(std::vector<DocumentAndFrequency *> *documentList, std::string &title);
    std::string createTitle(std::vector<char *> &userQuery);
    void sortByFreq(std::vector<DocumentAndFrequency *> *documentList);

    std::vector<DocumentAndFrequency *> *notProcessor(std::vector<char *> &userQuery, std::vector<DocumentAndFrequency *> *goodWordList);
    std::vector<DocumentAndFrequency *> *andProcessor(std::vector<char *> &userQuery);

    char *stemAndPreserve(const char *word);
    int getInput(int lowerBound, int upperBound);

    void errorHandle(int e);
    void deleteObjects();
    void setToNull();
public:
    InteractiveMode(int consoleArgs, char **consolePaths);
    ~InteractiveMode();
    void run();
};

#endif // INTERACTIVEMODE_H
