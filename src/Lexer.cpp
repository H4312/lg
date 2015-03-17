#include "Lexer.h"
#include <fstream>
#include <iostream>

Lexer::Lexer()
{
    //ctor
}

Lexer::~Lexer()
{
    //dtor
}

bool Lexer::openFile(char* filename)
{
    string line;
    this->file.open(filename);
    if (this->file.is_open())
    {
        while ( getline (this->file,line) )
        {
            cout << line << '\n';
        }
        this->file.close();
        return true;
    }
    else
    {
        cerr << "Unable to open file";
        return false;
    }

}

void Lexer::closeFile()
{
    this->file.close();
}
