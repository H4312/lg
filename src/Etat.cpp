#include "Etat.h"

Etat::Etat()
{
    //ctor
}

Etat::~Etat()
{
    //dtor
}

void setGauche(TYPE coteGauche) {
	m_gauche = coteGauche;
}

void setDroite(list<Symbole*> coteDroite) {
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

