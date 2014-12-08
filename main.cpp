#include <chrono>
#include <ctime>
#include "searchengine.h"
#include "hashtable.h"
#include "IndexInterface.h"
#include "maintenancemode.h"
#include "interactivemode.h"
#include "stresstestmode.h"
#include "parser.h"
#include "avltree.h"


using namespace std;
using namespace rapidxml;

int getInput(int lowerBound, int upperBound)
{
    assert ( lowerBound < upperBound );
    string returnValue;
    cin >> returnValue;

    bool validInput = false;
    while(true)
    {
        for(size_t i = 0; i < returnValue.length(); ++i)
        {
            if(!isdigit(returnValue.at(i)))
            {
                validInput = false;
                break;
            }

            validInput = true;
        }

        if(validInput && atoi(returnValue.c_str()) >= lowerBound && atoi(returnValue.c_str()) <= upperBound)
            break; // Loop over, good input

        cout << "Invalid input, please re-enter: ";
        cin.ignore(100, '\n');
        cin >> returnValue;
    }

    return atoi(returnValue.c_str());
}

int main(int argc, char *argv[])
{

    cout << "Please select a mode: " << endl;
    cout << "0. Exit\n1. Maintenance Mode\n2. Interactive Mode\n3. Stress Test Mode" << endl;
    int decision = getInput(0, 3);

    if(decision == 1)
    {
        MaintenanceMode mode(argc, argv);
        mode.run();
    }
    else if(decision == 2)
    {
        InteractiveMode mode(argc, argv);
        mode.run();
    }
    else if(decision == 3)
    {
        StressTestMode mode(argc, argv);
        mode.run();
    }
    return 0;
}
