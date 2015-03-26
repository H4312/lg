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
        enum type getGauche();
        int getNbr();
    protected:
    private:
        list<Symbole*> m_droite;
        enum type m_gauche;
        int m_nbr;
};


#endif // ETAT_H
