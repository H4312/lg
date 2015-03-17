#ifndef LEXER_H
#define LEXER_H
#include <fstream>

#include "Symbole.h"


using namespace std;


class Lexer
{
    public:
        Lexer();
        virtual ~Lexer();
        bool openFile(char* filename);
        void closeFile();
        Symbole* readCurrent();
        Symbole* readNext();
        bool moveNext();

    protected:
    private:
        fstream file;


};

#endif // LEXER_H
