
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
	    bool m_isAffectee;
		std::string id;
		double val ;
		bool m_isConst;
	private:
};
class Declaration
{
	public:
		Declaration();
		Declaration(std::string);

		std::string getNom();
		void setNom(std::string nom);
		double getVal();
		void setVal(double val);
		
		bool isConst(retuen m_isConst);
		bool isAffectee(){return m_isAffectee;}
	
	protected:
		std::string nom;
		double val ;
		bool m_isAffectee;
		bool m_isConst;
	private:
};

#endif
