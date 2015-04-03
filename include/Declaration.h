
#if !defined(__lg_diag_classe_Declaration_h)
#define __lg_diag_classe_Declaration_h

#include <string>

class Declaration
{
	public:
		Declaration();
		Declaration(std::string);

		std::string getNom();
		void setNom(std::string nom);
		double getVal();
		void setVal(double val);
		bool isConst ;
		
	
	protected:
		std::string nom;
		double val ;
	private:
};

#endif