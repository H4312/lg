#include "Symbole.h"


Symbole::Symbole(enum type unType){
    m_type = unType;
    m_fils = new list<Symbole*>;
}

enum type Symbole::getType()
{
    return m_type;
}

void Symbole::ajouterFils(Symbole* symb)
{
    m_fils->push_front(symb);
}
