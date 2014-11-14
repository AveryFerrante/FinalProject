#include <iostream>
#include <fstream>
#include <cstring>
#include "parser.h"


using namespace std;


int main(int argc, char *argv[])
{
    Parser parse(argv[1]);
    parse.printNodeContents();
    parse.cleanBodyContents();



    return 0;
}
