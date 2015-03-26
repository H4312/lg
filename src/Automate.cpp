#include "Automate.h"

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


}

void Automate::analyser()
{
    if (currentSym==NULL)
    {
        currentSym = lexer.readNext();
        if (currentSym==NULL)
        {
            return;
        }
    }

    Etat* n = m_transitions.find(m_etats.top())->second.find(currentSym->getType())->second;

    if (n!=NULL)
    {
        decalage(n);
    }
    else
    {
        reduire();
    }
}

void Automate::decalage(Etat *etat)
{
    m_etats.push(etat);
    m_symboles.push(currentSym);
    currentSym=NULL;
}

void Automate::reduire()
{
    Etat* etat = m_etats.top();
    Symbole* s = new Symbole(etat->getGauche());
    for(int i = 0 ; i < etat->getNbr() ; i++ )
    {
        s->ajouterFils(m_symboles.top());
        m_etats.pop();
        m_symboles.pop();
    }
    currentSym = s;
}
