#ifndef SYMBOLE_H
#define SYMBOLE_H
#include <string>
#include <list>

using namespace std;

class Symbole
{
    public:

    enum TYPE
    {P, BD, BI, D, pv, E, I, val, L, cons, var, C, v, id, eq, ecrire, O, lire, aff, opA, T, opM, F, po, pf, pl, mn, mul, divi};

    Symbole(TYPE unType);

    virtual ~Symbole();



    TYPE getType();
        void ajouterFils(Symbole*);
    protected:
    private:
        TYPE m_type;
        string m_nom;
        double m_value;
        list<Symbole*>* m_fils;
};


#endif // SYMBOLE_H
