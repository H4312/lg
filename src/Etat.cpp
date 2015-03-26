#include "Etat.h"

Etat::Etat()
{
    //ctor
}

Etat::~Etat()
{
    //dtor
}


enum type Etat::getGauche()
{
    return m_gauche;
}

int Etat::getNbr()
{
    return m_nbr;
}

