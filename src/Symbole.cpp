#include <iostream>
#include "Symbole.h"

using namespace std ;

// Constructeur
Symbole::Symbole(Symbole::TYPE unType){
    m_type = unType;
    m_fils = new list<Symbole*>;
}

// Destructeur
Symbole::~Symbole() 
{
	for(auto el : *m_fils)
	{		
		el->~Symbole();
		delete el->m_fils;
	}	
}

// Getter
Symbole::TYPE Symbole::getType()
{
    return m_type;
}

string Symbole::getNom()
{
    return m_nom;
}

int Symbole::getValeur()
{
    return m_valeur;
}

// Setter
void Symbole::setNom(string nom)
{
    m_nom = nom;
}

void Symbole::setValeur(int valeur)
{
    m_valeur = valeur;
}

// Méthodes privées

/*
 * Permet de construire la table de déclarations 'table' passée en paramètre
 */
void Symbole::construireTableDeclarations(TableDeclarations *table)
{
	switch(m_type)
	{
		// On appelle récursivement la fonction si on a un bloc déclaratif jusqu'à trouver une déclaration
		case(Symbole::P) :
		case(Symbole::BD) :
			for(auto el : *m_fils) 
			{
				el->construireTableDeclarations(table);
			}
			break;
		case(Symbole::D) :
			for(auto el : *m_fils) 
			{
				switch(el->m_type)
				{
					// Si on a une liste de variable on appelle la fonction adaptée
					case(Symbole::L) :
						el->construireDeclarationVar(table);	
						return;
					// Si on a des constantes on appelle la fonction adaptée
					case(Symbole::C) :
						el->construireDeclarationConst(table);
						return ;
					default :
						break;
				}
				el->construireTableDeclarations(table);
			}
		default :
			break;
	}
}

/*
 * Permet de construire la déclaration de variable et de l'ajouter à la table passée en paramètre
 */
void Symbole::construireDeclarationVar(TableDeclarations *table)
{
	for(auto el : *m_fils) 
	{
		switch(el->m_type)
		{
			// Tant qu'on a pas un id on appelle récursivement
			case(Symbole::L) :
			{
				el->construireDeclarationVar(table);
				break;
			}
			// Si on a un id on rajoute la déclaration à la table
			case(Symbole::id) :
			{
				DeclarationVar var(el->m_nom);
				table->ajouterDeclaration(var);
				return;
			}
			default :
				break;
		}
	}
}

/*
 * Permet de construire la déclaration de constante et de l'ajouter à la table passée en paramètre
 */
void Symbole::construireDeclarationConst(TableDeclarations *table)
{
	DeclarationConst constante;
	for (auto el : *m_fils)
	{
		switch(m_type)
		{
			// Tant qu'on a pas un id on appelle récursivement
			case(Symbole::C) :
			{
				el->construireDeclarationConst(table);
				break;
			}
			// Si on a un id on set le nom
			case(Symbole::id) :
			{
				constante.setNom(el->m_nom);
				break;
			}
			// Si on a la val on la set et on rajoute la déclaration à la table
			case(Symbole::val) :
			{
				constante.setVal(el->m_valeur);
				table->ajouterDeclaration(constante);
				return ;
			}
			default :
				break;
		}
	}
}

//Permet de construire la table des déclarations pour l'analyse statique
void Symbole::analyserStatiquement()
{
	TableDeclarations table;
	construireTableDeclarations(&table);
	analyseStatique(table);
}

//L'analyseur statique
void Symbole::analyseStatique(TableDeclarations table)
{
    TYPE type = this->getType();
    list<Symbole*> *fils = this->m_fils;
   
    switch(type)
    {
        case(Symbole::P) :
            {
                for (list<Symbole*>::iterator it=fils->begin(); it != fils->end(); ++it)
                {
                    (*it)->analyseStatique(table);
                }
            }
			break;
		case(Symbole::BI) :
        case(Symbole::O) :
        case(Symbole::F) :
        case(Symbole::T) :
            {
                for (list<Symbole*>::iterator it=fils->begin(); it != fils->end(); ++it)
                {
                    (*it)->analyseStatique(table);
                }
            }
			break;
        case(Symbole::I):
            {
                list<Symbole*>::iterator it=fils->begin();
                TYPE typeFils = (*it)->getType();
                

                if (fils->size()>0)
                {
					switch(typeFils)
					{
					case(Symbole::id) :
						{
							string nomLire = (*it)->getNom();
							Declaration* declarationLire = table.findById(nomLire);
							if(declarationLire == nullptr)
							{
								cerr<<"Erreur dans l'analyse statique: Variable affectée non déclarée"<<endl;
							}
							else if(declarationLire->isConst())
							{
								cerr<<"Erreur dans l'analyse statique: Constante ne pas pas être modifiée"<<endl;
							}
						}
						break;
						case(Symbole::lire) :
						{
							string nomLire = (*(--fils->end()))->getNom();
							Declaration* declarationLire = table.findById(nomLire) ;
							if(declarationLire == 0)
							{
								cerr<<"Erreur dans l'analyse statique: Variable lue non déclarée"<<endl;
							}
						}
						break;
						case(Symbole::ecrire) :
						{
							string nomLire = (*(--fils->begin()))->getNom();
							Declaration* declarationLire = table.findById(nomLire) ;
							if(declarationLire == 0)
							{
								cerr<<"Erreur dans l'analyse statique: Variable écrite non déclarée"<<endl;
							}
						}
						break;
					}
                }

            }
            break;
            
		}       
}

/*
 * Permet d'exécuter le code lutin
 */
void Symbole::exec(TableDeclarations* table)
{
	switch(m_type)
	{
		// On appelle récursivement executer jusqu'à tomber sur une I (instruction) ou sur un BD (bloc déclaratif)
		case(Symbole::P) :
		case(Symbole::BI) :
			for (auto el : *m_fils)
			{
				el->exec(table);
			}
			break;
		// Si on a un bloc déclaratif on construit la table des symboles
		case(Symbole::BD) :
			for (auto el : *m_fils)
			{
				el->construireTableDeclarations(table);
			}
			break;
		// Si on a une instruction
		case(Symbole::I) : 
			{
				// On regarde le type du 1er de ses fils et éxecute en fonction de l'instruction
				switch((*m_fils->begin())->m_type)
				{
					case(Symbole::ecrire) :
					{
						cout << (*(--m_fils->end()))->eval(table) << endl ;
						return;
					}
					case(Symbole::lire) : 
					{
						bool erreurFormatNombre = true;
						int entreeClavier;
						cin >> entreeClavier;
						// On boucle jusqu'à ce que l'entrée soit bien un nombre
						while(cin.fail())
						{
							erreurFormatNombre = true;
							cerr << "Veuillez entrer un nombre correct : " << endl;
							cin >> entreeClavier;

						}

						// On récupère le nom de la variable à affecter 
						string nomLire = (*(++m_fils->begin()))->m_nom;
						// On cherche dans la table la déclaration associée
						Declaration* declarationLire = table->findById(nomLire) ;
						declarationLire->setVal(entreeClavier);
						return;
					}
					case(Symbole::id) : 
					{
						// On récupère le nom de la variable à affecter 
						string nomAff = (*m_fils->begin())->m_nom;
						// On cherche dans la table la déclaration associée
						Declaration* declarationAff = table->findById(nomAff) ;
						// On recupère le dernier fils de l'instruction et on evalue pour pouvoir l'affecter
						declarationAff->setVal((*(--m_fils->end()))->eval(table));
						return;
					}
					default :
						break;
				}
			}
		default :
			break;
	}

}

// Méthodes publiques

/*
 * Permet d'ajouter un fils à un symbole
 */
void Symbole::ajouterFils(Symbole* symb)
{
    m_fils->push_front(symb);
}

/*
 * Permet d'évaluer un arbre de symbole afin d'effectuer les opérations
 */
int Symbole::eval(TableDeclarations* table)
{
	// On a soit 1 m_fils soit 3, si on a 3 il faut vérifier l'opération à faire
	if(m_fils->size()>1)
	{
		list<Symbole*>::const_iterator itDebut= m_fils->begin(); 
		list<Symbole*>::const_iterator itMilieu=++m_fils->begin();
		list<Symbole*>::const_iterator itFin=--m_fils->end(); 
		
		switch((*itMilieu)->getType())
		{
			// Si on tombe sur un opérateur additif
			case(Symbole::opA) :
			{
				list<Symbole*>::const_iterator operateur=(*itMilieu)->m_fils->begin(); 
				// On vérifie si on a un + ou un -
				switch((*operateur)->m_type)
				{
					case(pl) :
						// On evalue le sous arbre gauche + sous arbre droit
						return ((*itDebut)->eval(table)+(*itFin)->eval(table));
					case(mn) :
						// On evalue le sous arbre gauche - sous arbre droit
						return (*itDebut)->eval(table)-(*itFin)->eval(table);
					default : 
						break;
				}
			}
			break;
			// Si on tombe sur un opérateur multiplicatif
			case(Symbole::opM) :
			{
				list<Symbole*>::const_iterator operateur=(*itMilieu)->m_fils->begin(); 
				// On vérifier si on un * ou un /
				switch((*operateur)->m_type)
				{
					case(mul) :
						// On evalue le sous arbre gauche * sous arbre droit
						return ((*itDebut)->eval(table)*(*itFin)->eval(table));
					case(divi) :
						// On evalue le sous arbre gauche / sous arbre droit
						return ((*itDebut)->eval(table)/(*itFin)->eval(table));
					default : 
						break;
				}
			}
			break;
			// Si le milieu est O (ie on a des parenthèses), il faut évaluer ses m_fils
			case(Symbole::O) :
				return (*itMilieu)->eval(table);
			default :
				break;
		}
	}
	// Si on qu'un seul m_fils on parcours les m_fils jusqu'à récupérer la valeur
	else if(m_fils->size() == 1)
	{
		switch((*m_fils->begin())->m_type)
		{
			case(Symbole::T) :
			case(Symbole::F) :
			case(Symbole::val) :
			case(Symbole::id) : 
			{
				return (*m_fils->begin())->eval(table);
			}
			default :
				break;
		}
	}
	// Si on a pas de fils c'est qu'on a soit un id soit une val
	else if(m_fils->size() == 0)
	{
		switch(m_type) 
		{
			case(Symbole::val) :
				return m_valeur;
			case(Symbole::id) : 
			{
				Declaration* declaration = table->findById(m_nom) ;
				return declaration->getVal();
			}
			default :
				break;
		}
	}
}


string Symbole::toString() {
	string result = "";
    switch(m_type)
    {
        case pv : return ";\n";
        case val : return to_string(m_valeur);
        case cons : return "";
        case var : return "";
        case v : return "";
        case id : return m_nom;
        case eq : return "=";
        case ecrire : return "ecrire ";
        case lire : return "lire ";
        case aff : return ":= ";
        case po : return "(";
        case pf : return ")";
        case pl : return "+";
        case mn : return "-";
        case mul : return "*";
        case divi : return "/";
		case C :
			result = "";
			for(Symbole *s : *m_fils) {

				if(s->m_type==id){
					result = result +"const " + s->toString()+ "";
				} else if(s->m_type==v) {
					result += ";\n";
				} else  {
					result = result + s->toString();
				}
			}
			return result;
		case L :
			result = "";
			for(Symbole *s : *m_fils) {

				if(s->m_type==id){
					result += "var " + s->toString();
				} else if(s->m_type==v) {
					result += ";\n";
				} else {
					result += s->toString();
				}
			}
			return result;
        default:
            string result = "";
            for(Symbole *s : *m_fils) {

                result = result + s->toString();
            }
            return result;
    }
}

string Symbole::toString1() {

    switch(m_type)
    {
        case pv : return ";";
        case val : return "val : " +to_string(m_valeur);
        case cons : return "cons ";
        case var : return "var ";
        case v : return ", ";
        case id : return "id : " + m_nom;
        case eq : return "=";
        case ecrire : return "ecrire ";
        case lire : return "lire ";
        case aff : return ":= ";
        case po : return "(";
        case pf : return ")";
        case pl : return "+";
        case mn : return "-";
        case mul : return "*";
        case divi : return "/";
        case BD : return "BD";
        case BI : return "BI";
        case L : return "L";
        case O : return "O";
        case C : return "C";
        case D : return "D";
        case I : return "I";
        case T : return "T";
        case F : return "F";
        case opA : return "opA";
        case opM : return "opM";
        case P : return "P";
        case defaut : return "defaut";
        default:
            string result = "";
            return result;
    }
}
