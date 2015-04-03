#if !defined(__lg_diag_classe_DeclarationVar_h)
#define __lg_diag_classe_DeclarationVar_h

#include <Declaration.h>
#include <string>

class DeclarationVar : public Declaration
{
	public:
		DeclarationVar(std::string id) : Declaration(id){m_isConst = false;}
		void setIsAffectee(bool test){m_isAffectee = test;}
	protected:
	private:
};

#endif
