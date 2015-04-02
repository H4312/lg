#if !defined(__lg_diag_classe_TableSymbole_h)
#define __lg_diag_classe_TableSymbole_h

#include "Declaration.h"
#include "DeclarationVar.h"
#include "DeclarationConst.h"
#include <list>

using namespace std ;

class TableDeclarations
{
	public:
		void ajouterDeclaration(Declaration declaration);
		std::list<Declaration> declarations;
		Declaration* findById(string id);

	protected:
	private:
};

#endif