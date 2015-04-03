#include "TableDeclarations.h"
#include <iostream>

using namespace std;

void TableDeclarations::ajouterDeclaration(Declaration declaration)
{
   this->declarations.push_back(declaration);
}

Declaration* TableDeclarations::findById(string id)
{
	for (list<Declaration>::iterator it=declarations.begin(); it != declarations.end(); ++it)
	{
		if((*it).getNom().compare(id) == 0)
		{
			return &(*it); 
		}
	}
	return nullptr;
}

void TableDeclarations::afficherTable()
{
	for (list<Declaration>::iterator it=declarations.begin(); it != declarations.end(); ++it)
	{	
		cout << (*it).getNom() << endl;; 
		
	}
}