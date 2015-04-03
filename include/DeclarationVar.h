#if !defined(__lg_diag_classe_DeclarationVar_h)
#define __lg_diag_classe_DeclarationVar_h

#include <Declaration.h>
#include <string>

class DeclarationVar : public Declaration
{
	public:
		DeclarationVar(std::string nom) : Declaration(nom){}
		const bool isConst =false;
	protected:
	private:
};

#endif