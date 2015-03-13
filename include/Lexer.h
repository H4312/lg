#ifndef LEXER_H
#define LEXER_H

#include "Symbole.h"


class Lexer
{
    public:
        Lexer();
        virtual ~Lexer();
        Symbole* readCurrent();
        Symbole* readNext();
        bool moveNext();
    protected:
    private:
};

#endif // LEXER_H
