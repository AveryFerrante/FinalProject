#ifndef STRESSTESTMODE_H
#define STRESSTESTMODE_H
#include "IndexInterface.h"
#include "hashtable.h"
#include "parser.h"
#include "documentindex.h"
#include <windows.h>
#include "interactivemode.h" // This has the most functionality, can't / don't want to copy all of the code into here

#define INPUT_FILE_OPEN_ERROR 1234321

class StressTestMode : public InteractiveMode
{
private:
    IndexInterface *dataStructure;
    Parser *parse;
    DocumentIndex *documentIndexObject;


    // UTILITY FUNCTIONS

    void errorHandle(int e);


    void clearScreen();
    void pause();
public:
    StressTestMode(int consoleArgs, char **consolePaths);
    void run();
};

#endif // STRESSTESTMODE_H
