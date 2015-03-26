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
        void setDroite(list<Symbole*>);
        void setGauche(TYPE);
        int getNbr();
    protected:
    private:
        list<Symbole*> m_droite;
        TYPE m_gauche;
        int m_nbr;
};


#endif // ETAT_H
