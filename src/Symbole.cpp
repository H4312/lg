#include <iostream>
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

list<Symbole*>* Symbole::getFils()
{
    return m_fils;
}

Symbole::~Symbole() {
    delete m_fils;

}

void Symbole::afficher() {

    switch(m_type)
    {
        case pv : cout << ";\n"; break;
        case val : cout << m_value; break;
        case cons : cout << "cons "; break;
        case var : cout << "var "; break;
        case v : cout << ", "; break;
        case id : cout << m_nom; break;
        case eq : cout << "="; break;
        case ecrire : cout << "ecrire "; break;
        case lire : cout << "lire "; break;
        case aff : cout << ":= "; break;
        case po : cout << "("; break;
        case pf : cout << ")"; break;
        case pl : cout << "+"; break;
        case mn : cout << "-"; break;
        case mul : cout << "*"; break;
        case divi : cout << "/"; break;
        default:
            list<Symbole *> *fils = this->getFils();
            for(Symbole *s : *fils) {
                s->afficher();
            }
            break;
    }
}

