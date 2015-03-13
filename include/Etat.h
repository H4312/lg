#ifndef ETAT_H
#define ETAT_H

#include "Automate.h"
#include "Symbole.h"


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
