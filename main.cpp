#include <chrono>
#include <ctime>
#include "maintenancemode.h"
#include "interactivemode.h"
#include "parser.h"
#include "avltree.h"


using namespace std;
using namespace rapidxml;

int main(int argc, char *argv[])
{

    cout << "Please select a mode: " << endl;
    cout << "0. Exit\n1. Maintenance Mode\n2. Interactive Mode" << endl;
    int decision;
    cin >> decision;

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
    else
        cout << "Unknown Input. Exiting...." << endl;


    return 0;
}
