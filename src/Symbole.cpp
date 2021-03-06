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
	m_fils->clear();	
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
				if(table->findById(el->m_nom))
				{
					cerr << "La variable '" << el->m_nom << "' a déjà été déclarée" << endl;
				}
				else table->ajouterDeclaration(var);
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
		switch(el->m_type)
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
				//cout << el->m_nom << endl;
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

/*
 * Permet d'initialiser l'analyse statique avec paramètre et d'en analyser les retours
 */
void Symbole::analyserStatiquement()
{
	int retour = 0;
	TableDeclarations table;
	construireTableDeclarations(&table);
	analyseStatique(&table);
	for(auto el : table.declarations)
	{
		if(!el.isConstante() && el.isUtilisee() && !el.isAffectee())
		{
			cerr << "Erreur dans l'analyse statique : Variable '" << el.getNom() << "' déclarée, utilisée mais non affectée" << endl;
		}
		else if(!el.isConstante() && !el.isUtilisee() && el.isAffectee())
		{
			cerr << "Erreur dans l'analyse statique : Variable '" << el.getNom() << "' déclarée, affecté mais non utilisée" << endl;
		}
		else if(!el.isConstante() && !el.isUtilisee() && !el.isAffectee())
		{
			cerr << "Erreur dans l'analyse statique : Variable '" << el.getNom() << "' déclarée mais non affectée et non utilisée" << endl;
		}
	}
}

/*
 * Permet d'effectuer l'analyse statique
 */
void Symbole::analyseStatique(TableDeclarations *table)
{
    TYPE type = this->getType();
    list<Symbole*> *fils = this->m_fils;
   
    switch(type)
    {
        case(Symbole::P) :
        case(Symbole::BI) :
        {
            for (list<Symbole*>::iterator it=fils->begin(); it != fils->end(); ++it)
            {
                (*it)->analyseStatique(table);
            }
        }
		break;
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
							string nom = (*it)->m_nom ;
							Declaration* declaration = table->findById(nom);
							if(declaration == nullptr)
							{
								cerr << "Erreur dans l'analyse statique : Variable '" << nom << "' affectée non déclarée" << endl;
							}
							else if(declaration->isConstante())
							{
								cerr << "Erreur dans l'analyse statique : Constante '" << nom << "' ne pas pas être modifiée" << endl;
							}
							else if(declaration != nullptr && !declaration->isConstante())
							{
								declaration->setIsAffectee(true);
							}
						}
						break;
						case(Symbole::lire) :
						{
							string nom = (*(--fils->end()))->getNom();
							Declaration* declaration = table->findById(nom) ;
							if(declaration == 0)
							{
								cerr << "Erreur dans l'analyse statique : Variable '" << nom << "' lue non déclarée" <<endl;
							}
							else if(declaration != nullptr && !declaration->isConstante())
							{
								declaration->setIsAffectee(true);
							}
						}
						break;
						case(Symbole::ecrire) :
						{
							(*(--fils->end()))->analyseStatique(table);	
						}
						break;
						default:
							break;
					}
                }
            }
            break; 
		case(Symbole::id) :
		{
			Declaration* declaration = table->findById(m_nom) ;
			if(declaration == nullptr)
			{
				cerr << "Erreur dans l'analyse statique : Variable '" << m_nom << "' écrite non déclarée" <<endl;
			}
			else if(declaration != nullptr && !declaration->isConstante())
			{
				declaration->setIsUtilisee(true);
			}
			break;	
		} 
		default :
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
						// On récupère le nom de la variable à affecter 
						string nomLire = (*(++m_fils->begin()))->m_nom;
						// On cherche dans la table la déclaration associée
						Declaration* declarationLire = table->findById(nomLire) ;
						if(!declarationLire->isConstante())
						{
							bool erreurFormatNombre = true;
							int entreeClavier;
							cin >> entreeClavier;
							// On boucle jusqu'à ce que l'entrée soit bien un nombre
							while(cin.fail())
							{
								erreurFormatNombre = true;
								cerr << "Veuillez entrer un nombre correct : " << endl;
								cin.clear();
								cin.ignore(256,'\n');
								cin >> entreeClavier;

							}
							// On recupère le dernier fils de l'instruction et on evalue pour pouvoir l'affecter
							declarationLire->setVal(entreeClavier);
						}
						else 
						{
							cerr << "Une constante ne peut être modifiée" << endl;
							exit(1);
						}
						return;
					}
					case(Symbole::id) : 
					{
						// On récupère le nom de la variable à affecter 
						string nomAff = (*m_fils->begin())->m_nom;
						// On cherche dans la table la déclaration associée
						Declaration* declarationAff = table->findById(nomAff) ;
						if(!declarationAff->isConstante())
						{
							// On recupère le dernier fils de l'instruction et on evalue pour pouvoir l'affecter
							declarationAff->setVal((*(--m_fils->end()))->eval(table));
						}
						else 
						{
							cerr << "Une constante ne peut être modifiée" << endl;
							exit(1);
						}
						
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
	
		switch((*itMilieu)->m_type)
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
					{
						// On evalue le sous arbre gauche / sous arbre droit
						int droit = (*itFin)->eval(table);
						if(droit == 0)
						{
							cerr << "Erreur : Division par 0, arrêt du programme" << endl;
							exit(1);
						}
						else return ((*itDebut)->eval(table)/(*itFin)->eval(table));
					}
					default : 
						break;
				}
			}
			break;
			// Si le milieu est O (ie on a des parenthèses), il faut évaluer ses m_fils
			case(Symbole::O) :
			case(Symbole::val) :
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

void Symbole::transformation()
{
	TableDeclarations table;
	transformation(&table);
}

void Symbole::transformation(TableDeclarations *table)
{
	switch(m_type)
	{
		// On appelle récursivement transformation jusqu'à tomber sur une O (opération)
		case(Symbole::P) :
		case(Symbole::BI) :
		case(Symbole::I) :
		{
			for (auto el : *m_fils)
			{
				el->transformation(table);
			}
			break;
		}
		// Si on a BD on construit la table de déclaration locale
		case(Symbole::BD) :
		{
			for (auto el : *m_fils)
			{
				el->construireTableDeclarations(table);
			}
			break;
		}
		case(Symbole::O) :
		{
			operationConstante(table);
			break;
		}
		default :
			break;
	}
}

bool Symbole::operationConstante(TableDeclarations *table)
{
	switch(m_type)
	{
		case(Symbole::O) :
		case(Symbole::F) :
		case(Symbole::T) :
		{
			// On appelle récursivement jusqu'à tomber sur un id
			bool tousConst = true;
			for (auto el : *m_fils)
			{
				bool estConst = el->operationConstante(table);
				tousConst = tousConst && estConst ;
			}
			// Si toutes les operandes sont constantes on remplace par la valeur et on change le type du symbole
			if(tousConst) 
			{
				m_valeur = eval(table);
				m_type = Symbole::val;
				m_fils->clear();
			} 
			return tousConst ; 
		}
		case(Symbole::id) :
		{
			Declaration* declaration = table->findById(m_nom) ;
			// Si l'id est celui d'une constante on remplace par sa valeur 
			if(declaration->isConstante())
			{ 
				m_type = Symbole::val;
				m_nom = "";
				m_valeur = declaration->getVal();
				return true;
			}
			return false;
		}
		// Pour traiter les fils de F tels que parentheses, ou les symboles d'opération (+, -, *, /)
		default :
			return true;
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
        case val : return "valeur";
        case cons : return "const";
        case var : return "var";
        case v : return ", ";
        case id : return "identificateur";
        case eq : return "=";
        case ecrire : return "ecrire";
        case lire : return "lire";
        case aff : return ":= ";
        case po : return "(";
        case pf : return ")";
        case pl : return "+";
        case mn : return "-";
        case mul : return "*";
        case divi : return "/";
        /*case BD : return "Bloc Déclaratif";
        case BI : return "Bloc Instructif";
        case L : return "Liste de variable";
        case O : return "Opération";
        case C : return "Liste de constante";
        case D : return "Déclaration";
        case I : return "Instruction";
        case T : return "Terme";
        case F : return "Facteur";
        case opA : return "opA";
        case opM : return "opM";
        case P : return "P";*/
        case defaut : return "defaut";
        default:
            string result = "";
            return result;
    }
}
