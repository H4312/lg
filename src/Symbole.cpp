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

string Symbole::toString() {

    switch(m_type)
    {
        case pv : return ";\n";
        case val : return to_string(m_value);
        case cons : return "cons ";
        case var : return "var ";
        case v : return ", ";
        case id : return m_nom;
        case eq : return "=";
        case ecrire : return "ecrire ";
        case lire : return "lire ";
        case aff : return ":= ";
        case po : return "(";
        case pf : return ")";
        case pl : return "+";
        case mn : return "-";
        case mul : return "*";
        case divi : return "/";
        default:
            string result = "";
            list<Symbole *> *fils = this->getFils();
            for(Symbole *s : *fils) {

                result = s->toString() + result;
            }
            return result;
    }
}

string Symbole::toString1() {

    switch(m_type)
    {
        case pv : return ";\n";
        case val : return "val : " +to_string(m_value);
        case cons : return "cons ";
        case var : return "var ";
        case v : return ", ";
        case id : return "id : " + m_nom;
        case eq : return "=";
        case ecrire : return "ecrire ";
        case lire : return "lire ";
        case aff : return ":= ";
        case po : return "(";
        case pf : return ")";
        case pl : return "+";
        case mn : return "-";
        case mul : return "*";
        case divi : return "/";
        case BD : return "BD";
        case BI : return "BI";
        case L : return "L";
        case O : return "O";
        case C : return "C";
        case D : return "D";
        case I : return "I";
        case T : return "T";
        case F : return "F";
        case opA : return "opA";
        case opM : return "opM";
        case P : return "P";
        case defaut : return "defaut";
        default:
            string result = "";
            return result;
    }
}

void Symbole::setValue(double d) {
    m_value = d;
}

void Symbole::setName(string name) {
    m_nom = name;
}
