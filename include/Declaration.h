
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
		bool isConstante(){return m_isConst;}
		bool isAffectee(){return m_isAffectee;}
		bool isUtilisee(){return m_isUtilisee;}
		void setIsAffectee(bool isAffectee);
		void setIsUtilisee(bool isUtilisee);
		const bool isConst = false;

	
	protected:
		std::string nom;
		double val ;
		bool m_isAffectee;
		bool m_isConst;
		bool m_isUtilisee;
	private:
};

#endif
