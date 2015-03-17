#ifndef AUTOMATE_H
#define AUTOMATE_H

#include <string>

#include "Symbole.h"
#include "Etat.h"
#include "Lexer.h"
using namespace std;


class Automate
{
    public:
        Automate();
        void lecture(char* filename);
        void decalage(Symbole* sym, Etat* etat);
        virtual ~Automate();
    protected:
    private:
        Lexer lexer;
};

#endif // AUTOMATE_H
