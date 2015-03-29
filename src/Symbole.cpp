#include "Symbole.h"
#include <iostream>

using namespace std ;

Symbole::Symbole(enum type unType){
    m_type = unType;
    m_fils = new list<Symbole*>;
}

Symbole::Symbole(enum type unType, string nom){
    m_type = unType;
    m_nom = nom;
    m_fils = new list<Symbole*>;
}

enum type Symbole::getType()
{
    return m_type;
}

list<Symbole*> Symbole::getFils()
{
    return *m_fils;
}

void Symbole::ajouterFils(Symbole* symb)
{
    m_fils->push_back(symb);
}

void Symbole::setNom(string id)
{
    m_nom = id ;
}

string Symbole::getNom()
{
    return m_nom;
}

double Symbole::getValue()
{
    return m_value;
}

void Symbole::setValue(double value)
{
    m_value = value ;
}

void Symbole::ConstruireTableSymbole(TableSymbole &table){
	TYPE type = this->getType();
	list<Symbole*> fils = this->getFils() ;

	switch(type)
	{
		case(P) :
			for (list<Symbole*>::iterator it=fils.begin(); it != fils.end(); ++it)
			{
				(*it)->ConstruireTableSymbole(table);
			}
			break;
		case(BI) :
			break;
		case(BD) :
			for (list<Symbole*>::iterator it=fils.begin(); it != fils.end(); ++it)
			{
				(*it)->ConstruireTableSymbole(table);
			}
			break;
		case(D) :
			for (list<Symbole*>::iterator it=fils.begin(); it != fils.end(); ++it)
			{
				TYPE typeFils = (*it)->getType();
				switch(typeFils)
				{
					case(L) :
						(*it)->ConstruireDeclarationVar(table);	
						return;
					case(C) :
						(*it)->ConstruireDeclarationConst(table);
						return ;
					default :
						break;
				}
			}
		default :
			break;
	}
}

void Symbole::ConstruireDeclarationVar(TableSymbole &table){
	list<Symbole*> fils = this->getFils() ;

	for(auto el : fils) {
		switch(el->getType())
		{
			case(L) :
			{
				el->ConstruireDeclarationVar(table);
				break;
			}
			case(id) :
			{
				DeclarationVar var(el->getNom());
				table.AjouterDeclaration(var);
				return;
			}
			default :
				break;
		}
	}
/*
	for (list<Symbole*>::iterator it=fils.begin(); it != fils.end(); ++it)
	{
		cout << (*it)->getNom() << endl ;
		TYPE typeFils = (*it)->getType();
		switch(typeFils)
		{
			case(L) :
			{
				(*it)->ConstruireDeclarationVar(table);
			}
			case(id) :
			{
				DeclarationVar var((*it)->getNom());
				cout << ">>" << (*it)->getNom() << endl ;
				table.AjouterDeclaration(var);
				return;
			}
			default :
				break;
		}
	}
*/
}

void Symbole::ConstruireDeclarationConst(TableSymbole &table){
	list<Symbole*> fils = this->getFils() ;

	DeclarationConst constante;

	for (list<Symbole*>::iterator it=fils.begin(); it != fils.end(); ++it)
	{
		TYPE typeFils = (*it)->getType();
		switch(typeFils)
		{
			/*
			         /\_/\
			    ____/ o o \
			  /~____  =ø= /
			 (______)__m_m)
			  Bernie has been here.
			*/
			case(C) :
			{
				(*it)->ConstruireDeclarationConst(table);
				break;
			}
			case(id) :
			{
				constante.setNom((*it)->getNom());
				break;
			}
			case(val) :
			{
				constante.setVal((*it)->getValue());
				table.AjouterDeclaration(constante);
				return ;
			}
			default :
				break;
		}
	}
}

double Symbole::eval()
{
	list<Symbole*> fils = this->getFils();
	
	// On a soit 1 fils soit 3, si on a 3 il faut vérifier l'opération à faire
	if(fils.size()>1)
	{
		list<Symbole*>::const_iterator itDebut=fils.begin(); 
		list<Symbole*>::const_iterator itMilieu=++fils.begin();
		list<Symbole*>::const_iterator itFin=--fils.end(); 
		switch((*itMilieu)->getType())
		{
			case(opA) :
			{
				list<Symbole*>::const_iterator operateur=(*itMilieu)->getFils().begin(); 
				switch((*operateur)->getType())
				{
					case(pl) :
						return ((*itDebut)->eval()+(*itFin)->eval());
					case(mn) :
						return (*itDebut)->eval()-(*itFin)->eval();
					default : 
						break;
				}
			}
			break;
			case(opM) :
			{
				list<Symbole*>::const_iterator operateur=(*itMilieu)->getFils().begin(); 
				switch((*operateur)->getType())
				{
					case(mul) :
						return ((*itDebut)->eval()*(*itFin)->eval());
						break;
					case(divi) :
						return ((*itDebut)->eval()/(*itFin)->eval());
					default : 
						break;
				}
			}
			// Si le milieu est O (ie on a des parenthèses), il faut évaluer ses fils
			case(O) :
				return (*itMilieu)->eval();
			default :
				break;
		}
	}
	// Si on qu'un seul fils on parcours les fils jusqu'à récupérer la valeur
	else if(fils.size() == 1)
	{
		list<Symbole*>::const_iterator itDebut=fils.begin(); 
		switch((*itDebut)->getType())
		{
			case(T) :
				return (*itDebut)->eval();
			case(F) :
				return (*itDebut)->eval();
			case(val) :
				return (*itDebut)->getValue();
			// TODO case(id)
			default :
				break;
		}
		
	}

}


