#include <iostream>
#include "Automate.h"
#include "Symbole.h"
#include "TableSymbole.h"

class Automate;

using namespace std;

int main(int argc, char** argv)
{
	Automate a;
	Symbole* p = new Symbole(P);
	Symbole* bd = new Symbole(BD);
	Symbole* bd1 = new Symbole(BD);
	Symbole* bd2 = new Symbole(BD);
	Symbole* bd3 = new Symbole(BD);
	Symbole* d1 = new Symbole(D);
	Symbole* d2 = new Symbole(D);
	Symbole* var_ = new Symbole(var);
	Symbole* l = new Symbole(L);
	Symbole* l2 = new Symbole(L);
	Symbole* id_ = new Symbole(id, "x");

	cout << id_->getNom() << endl ;

	p->ajouterFils(bd);
	bd->ajouterFils(d1);
	d1->ajouterFils(var_);
	d1->ajouterFils(l);
	l->ajouterFils(l2);
	l->ajouterFils(id_);

	Symbole* cons_ = new Symbole(cons);
	Symbole* c = new Symbole(C);
	Symbole* id_2 = new Symbole(id, "y");
	Symbole* val_ = new Symbole(val);
	double valeur(5);
	val_->setValue(valeur);

	bd->ajouterFils(bd1);
	bd1->ajouterFils(d2);
	d2->ajouterFils(cons_);
	d2->ajouterFils(c);
	c->ajouterFils(id_2);
	c->ajouterFils(val_);
	
	TableSymbole table;
	p->ConstruireTableSymbole(table);
	table.afficherTable();

	cout << table.findById("y").getVal() << endl ;

	cout << endl;
	cout << endl;
	cout << endl;
	cout << endl;
    //Automate automate;
    //automate.lecture(argv[argc - 1]);
    return 0;
}
