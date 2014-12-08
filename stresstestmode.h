#ifndef STRESSTESTMODE_H
#define STRESSTESTMODE_H
#include "IndexInterface.h"
#include "hashtable.h"
#include "parser.h"
#include "documentindex.h"
#include <windows.h>
#include "interactivemode.h" // This has the most functionality, can't / don't want to copy all of the code into here
#include <chrono>
#include <ctime>

//Inherits from interactive mode to inherit its functionality
class StressTestMode : public InteractiveMode
{
private:
    Parser *parse;
    //Should make inputFile a member variable

    // UTILITY FUNCTIONS
    void loadCommand(std::ifstream &inputFile);
    void parseCommand(std::ifstream &inputFile);
    void queryCommand(std::ifstream &inputFile);
    void addCommand(std::ifstream &inputFile);
    void delCommand();

    void setToNull();
    void deleteObjects();
public:
    StressTestMode(int consoleArgs, char **consolePaths);
    void run();
};

#endif // STRESSTESTMODE_H
