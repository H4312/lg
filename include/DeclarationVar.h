/***********************************************************************
 * Module:  DeclarationVar.h
 * Author:  vcaen
 * Modified: vendredi 20 mars 2015 11:49:00
 * Purpose: Declaration of the class DeclarationVar
 ***********************************************************************/

#if !defined(__lg_diag_classe_DeclarationVar_h)
#define __lg_diag_classe_DeclarationVar_h

#include <Declaration.h>
#include <string>

class DeclarationVar : public Declaration
{
	public:
		DeclarationVar(std::string id) : Declaration(id){}
	protected:
	private:

};

#endif