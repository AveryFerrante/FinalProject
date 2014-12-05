#ifndef STRESSTESTMODE_H
#define STRESSTESTMODE_H
#include "IndexInterface.h"
#include "hashtable.h"
#include "parser.h"
#include "documentindex.h"
#include <windows.h>
#include "interactivemode.h" // This has the most functionality, can't / don't want to copy all of the code into here

class StressTestMode : public InteractiveMode
{
private:
    Parser *parse;


    // UTILITY FUNCTIONS
    void loadCommand(std::ifstream &inputFile);
    void parseCommand(std::ifstream &inputFile);


    void deleteObjects();
public:
    StressTestMode(int consoleArgs, char **consolePaths);
    void run();
};

#endif // STRESSTESTMODE_H
