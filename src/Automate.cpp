#include "Automate.h"
#include <fstream>
#include <iostream>

using namespace std;

Automate::Automate()
{
    //ctor
}

Automate::~Automate()
{
    //dtor
}

void Automate::lecture(char* filename)
{
  string line;
  ifstream myfile (filename);
  if (myfile.is_open())
  {
    while ( getline (myfile,line) )
    {
      cout << line << '\n';
    }
    myfile.close();
  }

  else cout << "Unable to open file";
}
