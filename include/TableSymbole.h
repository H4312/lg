/***********************************************************************
 * Module:  TableSmybole.h
 * Author:  vcaen
 * Modified: vendredi 20 mars 2015 11:52:38
 * Purpose: Declaration of the class TableSmybole
 ***********************************************************************/

#if !defined(__lg_diag_classe_TableSymbole_h)
#define __lg_diag_classe_TableSymbole_h

#include "DeclarationVar.h"
#include "DeclarationConst.h"
#include <list>

using namespace std ;

class TableSymbole
{
public:
   bool AjouterDeclaration(Declaration declaration);
   std::list<Declaration> declarations;
   void afficherTable();
   Declaration* findById(string id);

	protected:
	private:

};

#endif