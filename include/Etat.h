#ifndef ETAT_H
#define ETAT_H


#include "Symbole.h"
class Automate;


class Etat
{
    public:
        Etat();
        virtual ~Etat();
        list<Symbole> getDroite();
        Symbole::TYPE getGauche();
        int getNbr();
		void setGauche(TYPE);
		void setDroite(list<TYPE>);
    protected:
    private:
        list<TYPE> m_droite;
        Symbole::TYPE m_gauche;
        int m_nbr;
};


#endif // ETAT_H
