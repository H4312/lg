#ifndef SYMBOLE_H
#define SYMBOLE_H
#include <string>
#include <list>

using namespace std;

typedef enum type
{P, BD, BI, D, pv, E, I, val, L, cons, C, v, id, eq, ecrire, O, lire, aff, opA, T, opM, F, po, pf, pl, mn, mul, divi} TYPE;

class Symbole
{
    public:
        Symbole(TYPE unType);
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
