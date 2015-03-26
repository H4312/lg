#include "Symbole.h"


Symbole::Symbole(Symbole::TYPE unType){
    m_type = unType;
    m_fils = new list<Symbole*>;
}

Symbole::TYPE Symbole::getType()
{
    return m_type;
}

void Symbole::ajouterFils(Symbole* symb)
{
    m_fils->push_front(symb);
}


Symbole::~Symbole() {
    delete m_fils;

}
