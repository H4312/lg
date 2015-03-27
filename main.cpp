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
	
	Symbole* bi = new Symbole(BI);
	Symbole* i = new Symbole(I);
	Symbole* o = new Symbole(O);
	Symbole* o2 = new Symbole(O);
	Symbole* opa = new Symbole(opA);
	Symbole* plus = new Symbole(pl);
	Symbole* t = new Symbole(T);
	
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

	p->ajouterFils(bd);
	p->ajouterFils(bi);
	
	bi->ajouterFils(i);
	i->ajouterFils(o);
	o->ajouterFils(o2);
	o->ajouterFils(opa);
	o->ajouterFils(t);
	
	opa->ajouterFils(plus);

	
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
	//table.afficherTable();
	o->eval();
	
    return 0;
}
