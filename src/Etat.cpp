#include "Etat.h"

Etat::Etat()
{
    //ctor
}

Etat::Etat(int id)
{
    m_id=id;
    reduction=false;
}

Etat::~Etat()
{
    //dtor
}

void Etat::setGauche(TYPE coteGauche) {
	m_gauche = coteGauche;
    reduction=true;
}

void Etat::setListeDroite(list<TYPE> coteDroite) {
	m_droite = coteDroite;
    m_nbr=m_droite.size();
}

void Etat::setNbDroite(int nb)
{
    m_nbr=nb;
}

void Etat::setId(int id)
{
    m_id=id;
}

Symbole::TYPE Etat::getGauche()
{
    return m_gauche;
}

int Etat::getNbr()
{
    return m_nbr;
}

int Etat::getId()
{
    return m_id;
}

bool Etat::hasReduction()
{
    return reduction;
}

