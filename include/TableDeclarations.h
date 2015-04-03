#ifndef TABLEDECLARATIONS_H
#define TABLEDECLARATIONS_H
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
		void afficherTable();
	protected:
	private:
};

#endif