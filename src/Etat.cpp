#include "Etat.h"

Etat::Etat()
{
    //ctor
}

Etat::~Etat()
{
    //dtor
}

void Etat::setGauche(TYPE coteGauche) {
	m_gauche = coteGauche;
}

void Etat::setDroite(list<TYPE> coteDroite) {
	m_droite = coteDroite;
}

Symbole::TYPE Etat::getGauche()
{
    return m_gauche;
}

int Etat::getNbr()
{
    return m_nbr;
}

