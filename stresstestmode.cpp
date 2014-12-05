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
               cout << "Load index instructions" << endl;

           else if(instruction == "clr")
               cout << "Delete index instructions" << endl;

           else if(instruction == "prse")
               cout << "Parse and index XML files" << endl;

           else if(instruction == "qry")
               cout << "Query instructions" << endl;

           else
               cout << "Unknown Command Encountered" << endl;
        }

    }
    catch(int e)
    {
        errorHandle(e);
    }
}






//***************************************************UTILITY FUNCTIONS******************************************

void StressTestMode::errorHandle(int e)
{
    clearScreen();
    cout << "ERROR ENCOUNTERED:" << endl;
    if(e == INPUT_FILE_OPEN_ERROR)
        cout << "Could not open the file entered by the user (see manual)" << endl;




    pause();
}









void StressTestMode::clearScreen() { system("cls"); }
void StressTestMode::pause() { system("pause"); }
