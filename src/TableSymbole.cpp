/***********************************************************************
 * Module:  TableSmybole.cpp
 * Author:  vcaen
 * Modified: vendredi 20 mars 2015 11:52:38
 * Purpose: Implementation of the class TableSmybole
 ***********************************************************************/

#include "Declaration.h"
#include "TableSymbole.h"
#include <iostream>

using namespace std;

////////////////////////////////////////////////////////////////////////
// Name:       TableSmybole::AjouterDeclaration(Declaration declaration)
// Purpose:    Implementation of TableSmybole::AjouterDeclaration()
// Parameters:
// - declaration
// Return:     bool
////////////////////////////////////////////////////////////////////////

bool TableSymbole::AjouterDeclaration(Declaration declaration)
{
   this->declarations.push_back(declaration);
}

void TableSymbole::afficherTable()
{
	for (list<Declaration>::iterator it=declarations.begin(); it != declarations.end(); ++it)
	{
		cout << (*it).getNom() << "=" << (*it).getVal() << endl ;
	}
}

Declaration TableSymbole::findById(string id)
{
	for(auto el : declarations) 
	{
		if(el.getNom().compare(id) == 0)
		{
			return el;
		}
	}
	//return nullptr;
}