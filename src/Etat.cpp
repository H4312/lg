#include "Etat.h"

Etat::Etat()
{
    //ctor
}

Etat::~Etat()
{
    //dtor
}


Symbole::TYPE Etat::getGauche()
{
    return m_gauche;
}

int Etat::getNbr()
{
    return m_nbr;
}

