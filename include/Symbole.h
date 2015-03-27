#ifndef SYMBOLE_H
#define SYMBOLE_H
#include <string>
#include <list>
#include "TableSymbole.h"

using namespace std;

typedef enum type
{P, BD, BI, D, pv, E, I, var, val, L, cons, C, v, id, eq, ecrire, O, lire, aff, opA, T, opM, F, po, pf, pl, mn, mul, divi} TYPE;
/*0  1   2  3   4  5  6   7    8   9   10   11 12 13  14   15    16   17   18   19   20  21  22 23  24  25  26  27     28*/

class Symbole
{
    public:
        Symbole(TYPE unType);
        Symbole(TYPE unType, string nom);
        TYPE getType();
        void ajouterFils(Symbole*);
        void ConstruireTableSymbole(TableSymbole &table);
        void ConstruireDeclarationVar(TableSymbole &table);
        void ConstruireDeclarationConst(TableSymbole &table);
       
        list<Symbole*> getFils() ;
        string getNom();
        void setNom(string id);
        double getValue();
        void setValue(double value);
        double eval();
    protected:
    private:
        TYPE m_type;
        string m_nom;
        double m_value;
        list<Symbole*>* m_fils;
};


#endif // SYMBOLE_H
