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
    int decision = -1;
    while(decision != 0)
    {
        cout << "Please select a mode: " << endl;
        cout << "0. Exit\n1. Maintenance Mode\n2. Interactive Mode" << endl;
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

    }

    return 0;
}
