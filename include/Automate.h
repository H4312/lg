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
        bool reduire();
		map<Etat*, map<Symbole::TYPE, Etat*> > initMap();
        virtual ~Automate();
    protected:
    private:
        Lexer lexer;
        map<Etat*, map<Symbole::TYPE , Etat*> > m_transitions;
        Symbole* currentSym=0;
        Symbole* programme=0;
        stack<Etat*> m_etats;
        stack<Symbole*> m_symboles;
        bool isRead=false;
};


#endif // AUTOMATE_H
