/***********************************************************************
 * Module:  Declaration.h
 * Author:  vcaen
 * Modified: vendredi 20 mars 2015 11:49:51
 * Purpose: Declaration of the class Declaration
 ***********************************************************************/

#if !defined(__lg_diag_classe_Declaration_h)
#define __lg_diag_classe_Declaration_h

#include <string>

class Declaration
{
	public:
		Declaration();
		Declaration(std::string);
		std::string getNom();
		double getVal();
		void setVal(double val);
		void setNom(std::string nom);
	protected:
		std::string id;
		double val ;
	private:
};

#endif