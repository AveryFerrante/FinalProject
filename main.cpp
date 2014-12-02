#include <chrono>
#include <ctime>
#include "maintenancemode.h"
#include "interactivemode.h"


using namespace std;
using namespace rapidxml;

int main(int argc, char *argv[])
{
    int decision = -1;
    while(decision != 0)
    {
        cout << "1. Maintenance Mode\n2. Interactive Mode" << endl;
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

    }

    return 0;
}
