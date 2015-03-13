#include <iostream>
#include "Automate.h"

using namespace std;

int main(int argc, char** argv)
{
    Automate automate;
    automate.lecture(argv[argc - 1]);
    return 0;
}
