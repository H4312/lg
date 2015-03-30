#ifndef LEXER_H
#define LEXER_H
#include <fstream>
#include <vector>
#include <list>

#include "Symbole.h"


using namespace std;


class Lexer
{
    public:
        Lexer();
        virtual ~Lexer();
        bool openFile(char  *filename);
        bool isFileOpen();
        void closeFile();
        Symbole* sonder();
        Symbole* readNext();
    bool moveNext();
    Symbole* getSymbole(string str);
    vector<string> * splitFileBySym();

    bool isIdentifier(string const &s);
    bool isInteger(string const &s);
    void DisplaySplittedFile();
    bool isOnlyDouble(char const *str);

protected:
private:
    std::list< pair<string,Symbole> > matchingMap;
    fstream file;
    int current_symbole = 0;
    vector<string> *splittedFile = new vector<string>;
    bool cursorNext();
    string readSymbole();
};

#endif // LEXER_H
