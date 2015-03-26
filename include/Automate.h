#ifndef AUTOMATE_H
#define AUTOMATE_H

#include <string>

#include "Symbole.h"
#include "Etat.h"
#include "Lexer.h"
#include <stack>
#include <map>

using namespace std;

class Automate
{
    public:
        Automate();
        void lecture(char* filename);
        void analyser();
        void decalage(Etat* etat);
        void reduire();
        virtual ~Automate();
    protected:
    private:
        Lexer lexer;
        map<Etat*, map<TYPE, Etat*> > m_transitions;
        Symbole* currentSym;
        stack<Etat*> m_etats;
        stack<Symbole*> m_symboles;
};


#endif // AUTOMATE_H
