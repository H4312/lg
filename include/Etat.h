#ifndef ETAT_H
#define ETAT_H


#include "Symbole.h"
class Automate;


class Etat
{
    public:
        Etat();
        virtual ~Etat();
        virtual bool transition(Automate& automate, Symbole& sym) = 0;
    protected:
    private:
};

#endif // ETAT_H
