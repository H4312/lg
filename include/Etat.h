#ifndef ETAT_H
#define ETAT_H


#include "Symbole.h"
class Automate;


class Etat
{
    public:
        Etat();
        Etat(int id);
        virtual ~Etat();
        list<Symbole> getListeDroite();
        int getNbDroite();
        Symbole::TYPE getGauche();
        int getNbr();
        int getId();
		void setGauche(TYPE);
        void setNbDroite(int nb);
		void setListeDroite(list<TYPE>);
        void setId(int id);
        bool hasReduction();
    protected:
    private:
        list<TYPE> m_droite;
        Symbole::TYPE m_gauche;
        int m_nbr;
        int m_id;
        bool reduction=false;
};


#endif // ETAT_H
