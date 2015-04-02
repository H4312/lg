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
        bool lecture(char* filename);
        Symbole * analyser();
        void decalage(Etat* etat);
        void exec();
        bool reduire();
		map<Etat*, map<Symbole::TYPE, Etat*> > initMap();
        Symbole* programme=0;
        virtual ~Automate();
    protected:
    private:
        Lexer lexer;
        TableDeclarations table;
        map<Etat*, map<Symbole::TYPE , Etat*> > m_transitions;
        Symbole* currentSym=0;
        stack<Etat*> m_etats;
        stack<Symbole*> m_symboles;
        bool isRead=false;
        int err=0;
};


#endif // AUTOMATE_H
