#ifndef SYMBOLE_H
#define SYMBOLE_H
#include <string>
#include <list>
#include <vector>
#include "TableDeclarations.h"

using namespace std;

class Symbole
{
    public:
        enum TYPE
        {P, BD, BI, D, pv, E, I, val, L, cons, var, C, v, id, eq, ecrire, O, lire, aff, opA, T, opM, F, po, pf, pl, mn, mul, divi, defaut};
        /*0  1   2  3   4  5  6   7   8   9   10   11  12 13  14   15    16   17   18   19   20  21  22 23  24  25  26  27     28*/ 
        Symbole(TYPE unType);
        virtual ~Symbole();
        
        // Getter & Setter
        TYPE getType();
        string getNom();
        void setNom(string id);
        int getValeur();
        void setValeur(int value);
        
        // Autres méthodes publiques
        string toString();
        string toString1();
        void ajouterFils(Symbole*);
        void exec(TableDeclarations *table);
        void analyserStatiquement();
        void transformation();
         
    protected:

    private:
        TYPE m_type;
        string m_nom;
        int m_valeur;
        list<Symbole*> *m_fils;

        void construireTableDeclarations(TableDeclarations *table);
        void construireDeclarationVar(TableDeclarations *table);
        void construireDeclarationConst(TableDeclarations *table);
        int eval(TableDeclarations *table); 
        void afficher() ;
        bool declarationSansUtilisation(string nom);
	void analyseStatique(TableDeclarations table);
        bool operationConstante(vector<string> *idConstantes, TableDeclarations *table);

};

typedef Symbole::TYPE TYPE;

#endif // SYMBOLE_H
