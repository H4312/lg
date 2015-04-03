#if !defined(__lg_diag_classe_DeclarationConst_h)
#define __lg_diag_classe_DeclarationConst_h

#include <Declaration.h>
#include <string>

class DeclarationConst : public Declaration
{
	public:
		DeclarationConst() : Declaration(){isConst=true;}
	protected:
	private:
};

#endif