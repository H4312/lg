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
        Symbole* readCurrent();
        Symbole* readNext();
        bool moveNext();
    void splitFileBySym();

    void DisplaySplittedFile();

protected:
    private:
        std::list< pair<string,Symbole>> matchingMap;
        fstream file;
        unsigned int current_line_number;
        unsigned int current_char_number;
        string current_line;
        string current_word;
        vector<string> *splittedFile = new vector<string>;
        bool cursorNext();
        string readSymbole();



};

#endif // LEXER_H
