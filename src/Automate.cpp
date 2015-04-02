#include <iostream>
#include "Automate.h"
#include "Symbole.h"

using namespace std;

Automate::Automate()
{
    /*ex = new list<Symbole*>();
    Symbole* s1 = new Symbole(var); ex->push_back(s1);
    Symbole* s2 = new Symbole(id); ex->push_back(s2);
    Symbole* s3 = new Symbole(v); ex->push_back(s3);
    Symbole* s4 = new Symbole(id); ex->push_back(s4);
    Symbole* s5 = new Symbole(pv); ex->push_back(s5);
*/
}

Automate::~Automate()
{
	delete programme;
}

bool Automate::lecture(char* filename)
{
	m_transitions = initMap();
	if(lexer.openFile(filename))
	{
		lexer.splitFileBySym();
		return true;
	}
	else return false;
}

Symbole* Automate::analyser() {
	bool end = false;
	err = 0;
	while (1) {
		isRead = false;
		if (currentSym == NULL) {
			currentSym = lexer.sonder();
			isRead = true;
			if (currentSym == NULL) {
				currentSym = new Symbole(Symbole::defaut);
				end = true;
			}
		}
		//cout << "Symbole courrant : " << currentSym->toString1() << endl;
		map<Symbole::TYPE, Etat *> temp = m_transitions.find(m_etats.top())->second;


		if (temp.find(currentSym->getType()) != temp.end()) {
			//cout << "Decalage de " << m_etats.top()->getId();
			Etat *n = temp.find(currentSym->getType())->second;
			//cout << " vers l'etat " << n->getId() << endl;
			decalage(n);
		}

		else {
			bool correct = reduire();
			if (!correct) {
				for(map<Symbole::TYPE, Etat *>::iterator p = temp.begin(); p != temp.end(); p++)
				{
					cout<<Symbole(p->first).toString1()<<" ";
				}
				cout<<" attendu"<<endl;
			}

			if (currentSym->getType() == Symbole::P) {
				if (end) {
					if (err == 0) cout << endl << "Analyse terminée - Syntaxe correcte" << endl;
					if (err > 0) cout << endl << "Analyse terminée - " << err << " Erreurs" << endl;
					programme = currentSym;
					return programme;
				}
				else {
					cout << "Erreur, Symbole inattendu " << endl;
					lexer.readNext();
				}
			}
		}
	}
}

void Automate::decalage(Etat *etat)
{
    m_etats.push(etat);
    m_symboles.push(currentSym);
	if(isRead)
	{
		lexer.readNext();
	}
    currentSym=NULL;
}

bool Automate::reduire()
{
	if(m_etats.top()->hasReduction())
	{
		Etat* etat = m_etats.top();
		Symbole* s = new Symbole(etat->getGauche());
		//cout<<"Reduction dans l'etat "<< etat->getId()<<" dans " << s->toString1()<<" de ";
		for(int i = 0 ; i < etat->getNbr() ; i++ )
		{
			s->ajouterFils(m_symboles.top());
			m_etats.pop();
			//cout<<m_symboles.top()->toString1()<<" ";
			m_symboles.pop();
		}
		currentSym = s;
		return true;
	}
	else {
		cout << endl <<"Symbole inattendu, depilage de " << m_etats.top()->getId() << endl;
		while (m_symboles.top()->getType() != Symbole::BD && m_symboles.top()->getType() != Symbole::BI && !m_symboles.empty())
		{
			//cout<<"Etat : "<< m_etats.top()->getId()<<" Symbole : "<<m_symboles.top()->toString1();
			m_symboles.pop();
			m_etats.pop();
		}
		lexer.readNext();
		err++;
		return false;
	}

}

void Automate::exec()
{
	programme->exec(&table);
}

map<Etat*, map<TYPE, Etat*> > Automate::initMap() {
	const int nombreEtats = 43;

	// Map pour les transitions
	map<Etat *, map<TYPE, Etat *> > m_transitions;

	// Initialiser un vector avec 43 pour les etats

	vector<Etat *> etats;
	for (int i = 1 ; i<=nombreEtats ; i++)
	{
		Etat* e = new Etat(i);
		etats.push_back(e);
	}


	// Initialiser tous les états
	list<TYPE> listeVide;

	etats[0]->setGauche(Symbole::BD);
	etats[0]->setListeDroite(listeVide);
	m_etats.push(etats[0]);

	etats[1]->setGauche(Symbole::BI);
	etats[1]->setListeDroite(listeVide);
	etats[1]->setId(2);

	etats[2]->setGauche(Symbole::P);
	list<TYPE> droite2;
	droite2.push_back(Symbole::BD);
	droite2.push_back(Symbole::BI);
	etats[2]->setListeDroite(droite2);
	etats[2]->setId(3);

	etats[10]->setGauche(Symbole::BD);
	list<TYPE> droite10;
	droite10.push_back(Symbole::BD);
	droite10.push_back(Symbole::D);
	droite10.push_back(Symbole::pv);
	etats[10]->setListeDroite(droite10);
	etats[10]->setId(11);

	etats[11]->setGauche(Symbole::D);
	list<TYPE> droite11;
	droite11.push_back(Symbole::var);
	droite11.push_back(Symbole::L);
	etats[11]->setListeDroite(droite11);
	etats[11]->setId(12);

	{etats[12]->setGauche(Symbole::L);
		list<TYPE> droite;
		droite.push_back(Symbole::id);
		etats[12]->setListeDroite(droite);
		etats[12]->setId(13);}

	{int i = 14;
		etats[i-1]->setGauche(Symbole::D);
		list<TYPE> droite;
		droite.push_back(Symbole::cons);
		droite.push_back(Symbole::C);
		etats[i-1]->setListeDroite(droite);
		etats[i-1]->setId(i);}

	{int i = 16;
		etats[i-1]->setGauche(Symbole::BI);
		list<TYPE> droite;
		droite.push_back(Symbole::BI);
		droite.push_back(Symbole::I);
		droite.push_back(Symbole::pv);
		etats[i-1]->setListeDroite(droite);
		etats[i-1]->setId(i);}

	{int i = 17;
		etats[i-1]->setGauche(Symbole::I);
		list<TYPE> droite;
		droite.push_back(Symbole::ecrire);
		droite.push_back(Symbole::O);
		etats[i-1]->setListeDroite(droite);
		etats[i-1]->setId(i);}

	{int i = 18;
		etats[i-1]->setGauche(Symbole::O);
		list<TYPE> droite;
		droite.push_back(Symbole::I);
		etats[i-1]->setListeDroite(droite);
		etats[i-1]->setId(i);}

	{int i = 19;
		etats[i-1]->setGauche(Symbole::T);
		list<TYPE> droite;
		droite.push_back(Symbole::F);
		etats[i-1]->setListeDroite(droite);
		etats[i-1]->setId(i);}

	{int i = 20;
		etats[i-1]->setGauche(Symbole::F);
		list<TYPE> droite;
		droite.push_back(Symbole::id);
		etats[i-1]->setListeDroite(droite);
		etats[i-1]->setId(i);}

	{int i = 21;
		etats[i-1]->setGauche(Symbole::F);
		list<TYPE> droite;
		droite.push_back(Symbole::val);
		etats[i-1]->setListeDroite(droite);
		etats[i-1]->setId(i);}
	{int i = 23;
		etats[i-1]->setGauche(Symbole::I);
		list<TYPE> droite;
		droite.push_back(Symbole::lire);
		droite.push_back(Symbole::id);
		etats[i-1]->setListeDroite(droite);
		etats[i-1]->setId(i);}
	{int i = 29;
		etats[i-1]->setGauche(Symbole::opA);
		list<TYPE> droite;
		droite.push_back(Symbole::pl);
		etats[i-1]->setListeDroite(droite);
		etats[i-1]->setId(i);}
	{int i = 30;
		etats[i-1]->setGauche(Symbole::opA);
		list<TYPE> droite;
		droite.push_back(Symbole::mn);
		etats[i-1]->setListeDroite(droite);
		etats[i-1]->setId(i);}
	{int i = 32;
		etats[i-1]->setGauche(Symbole::opM);
		list<TYPE> droite;
		droite.push_back(Symbole::mul);
		etats[i-1]->setListeDroite(droite);
		etats[i-1]->setId(i);}
	{int i = 33;
		etats[i-1]->setGauche(Symbole::opM);
		list<TYPE> droite;
		droite.push_back(Symbole::divi);
		etats[i-1]->setListeDroite(droite);
		etats[i-1]->setId(i);}
	{int i = 35;
		etats[i-1]->setGauche(Symbole::I);
		list<TYPE> droite;
		droite.push_back(Symbole::id);
		droite.push_back(Symbole::aff);
		droite.push_back(Symbole::O);
		etats[i-1]->setListeDroite(droite);
		etats[i-1]->setId(i);}
	{int i = 36;
		etats[i-1]->setGauche(Symbole::L);
		list<TYPE> droite;
		droite.push_back(Symbole::L);
		droite.push_back(Symbole::v);
		droite.push_back(Symbole::id);
		etats[i-1]->setListeDroite(droite);
		etats[i-1]->setId(i);}
	{int i = 38;
		etats[i-1]->setGauche(Symbole::C);
		list<TYPE> droite;
		droite.push_back(Symbole::id);
		droite.push_back(Symbole::eq);
		droite.push_back(Symbole::val);
		etats[i-1]->setListeDroite(droite);
		etats[i-1]->setId(i);}
	{int i = 39;
		etats[i-1]->setGauche(Symbole::O);
		list<TYPE> droite;
		droite.push_back(Symbole::O);
		droite.push_back(Symbole::opA);
		droite.push_back(Symbole::T);
		etats[i-1]->setListeDroite(droite);
		etats[i-1]->setId(i);}
	{int i = 40;
		etats[i-1]->setGauche(Symbole::T);
		list<TYPE> droite;
		droite.push_back(Symbole::T);
		droite.push_back(Symbole::opM);
		droite.push_back(Symbole::F);
		etats[i-1]->setListeDroite(droite);
		etats[i-1]->setId(i);}
	{int i = 41;
		etats[i-1]->setGauche(Symbole::F);
		list<TYPE> droite;
		droite.push_back(Symbole::po);
		droite.push_back(Symbole::O);
		droite.push_back(Symbole::pf);
		etats[i-1]->setListeDroite(droite);
		etats[i-1]->setId(i);}
	{int i = 43;
		etats[i-1]->setGauche(Symbole::C);
		list<TYPE> droite;
		droite.push_back(Symbole::C);
		droite.push_back(Symbole::v);
		droite.push_back(Symbole::id);
		droite.push_back(Symbole::eq);
		droite.push_back(Symbole::val);
		etats[i-1]->setListeDroite(droite);
		etats[i-1]->setId(i);}

	map<TYPE, Etat*> transitions_initialize;
	//transitions_initialize.insert(make_pair(Symbole::P, etats.at(1)));

	// Initialiser un vector avec 43 pour les transitions
	// et ajouter les transitions correspondantes
	// (Attention: etats.at(0) et E0 égal à l'état1 dans l'automate)
	vector< map<TYPE, Etat*> > transitions(nombreEtats, transitions_initialize);

	transitions[0].insert(make_pair(Symbole::BD, etats.at(1)));

	transitions[1].insert(make_pair(Symbole::BI, etats.at(2)));
	transitions[1].insert(make_pair(Symbole::D, etats.at(3)));
	transitions[1].insert(make_pair(Symbole::var, etats.at(4)));
	transitions[1].insert(make_pair(Symbole::cons, etats.at(5)));

	transitions[2].insert(make_pair(Symbole::ecrire, etats.at(7)));
	transitions[2].insert(make_pair(Symbole::lire, etats.at(8)));
	transitions[2].insert(make_pair(Symbole::id, etats.at(9)));
	transitions[2].insert(make_pair(Symbole::I, etats.at(6)));

	transitions[3].insert(make_pair(Symbole::pv, etats.at(10)));

	transitions[4].insert(make_pair(Symbole::L, etats.at(11)));
	transitions[4].insert(make_pair(Symbole::id, etats.at(12)));

	transitions[5].insert(make_pair(Symbole::C, etats.at(13)));
	transitions[5].insert(make_pair(Symbole::id, etats.at(14)));

	transitions[6].insert(make_pair(Symbole::pv, etats.at(15)));

	transitions[7].insert(make_pair(Symbole::O, etats.at(16)));
	transitions[7].insert(make_pair(Symbole::T, etats.at(17)));
	transitions[7].insert(make_pair(Symbole::F, etats.at(18)));
	transitions[7].insert(make_pair(Symbole::id, etats.at(19)));
	transitions[7].insert(make_pair(Symbole::val, etats.at(20)));
	transitions[7].insert(make_pair(Symbole::po, etats.at(21)));

	transitions[8].insert(make_pair(Symbole::id, etats.at(22)));

	transitions[9].insert(make_pair(Symbole::aff, etats.at(23)));

	// transitions[10] reste vide

	transitions[11].insert(make_pair(Symbole::v, etats.at(24)));

	// transitions[12] reste vide

	transitions[13].insert(make_pair(Symbole::v, etats.at(25)));

	transitions[14].insert(make_pair(Symbole::eq, etats.at(26)));

	// transitions[15] reste vide

	transitions[16].insert(make_pair(Symbole::opA, etats.at(27)));
	transitions[16].insert(make_pair(Symbole::pl, etats.at(28)));
	transitions[16].insert(make_pair(Symbole::mn, etats.at(29)));

	transitions[17].insert(make_pair(Symbole::opM, etats.at(30)));
	transitions[17].insert(make_pair(Symbole::mul, etats.at(31)));
	transitions[17].insert(make_pair(Symbole::opA, etats.at(32)));

	// transitions[18] reste vide
	// transitions[19] reste vide
	// transitions[20] reste vide

	transitions[21].insert(make_pair(Symbole::T, etats.at(17)));
	transitions[21].insert(make_pair(Symbole::F, etats.at(18)));
	transitions[21].insert(make_pair(Symbole::id, etats.at(19)));
	transitions[21].insert(make_pair(Symbole::val, etats.at(20)));

	// transitions[22] reste vide

	transitions[23].insert(make_pair(Symbole::T, etats.at(17)));
	transitions[23].insert(make_pair(Symbole::F, etats.at(18)));
	transitions[23].insert(make_pair(Symbole::id, etats.at(19)));
	transitions[23].insert(make_pair(Symbole::val, etats.at(20)));
	transitions[23].insert(make_pair(Symbole::po, etats.at(21)));
	transitions[23].insert(make_pair(Symbole::O, etats.at(34)));

	transitions[24].insert(make_pair(Symbole::id, etats.at(35)));

	transitions[25].insert(make_pair(Symbole::id, etats.at(36)));

	transitions[26].insert(make_pair(Symbole::val, etats.at(37)));

	transitions[27].insert(make_pair(Symbole::T, etats.at(38)));
	transitions[27].insert(make_pair(Symbole::F, etats.at(18)));
	transitions[27].insert(make_pair(Symbole::id, etats.at(19)));
	transitions[27].insert(make_pair(Symbole::val, etats.at(20)));
	transitions[27].insert(make_pair(Symbole::po, etats.at(21)));


	// transitions[28] reste vide
	// transitions[29] reste vide

	transitions[30].insert(make_pair(Symbole::id, etats.at(19)));
	transitions[30].insert(make_pair(Symbole::val, etats.at(20)));
	transitions[30].insert(make_pair(Symbole::po, etats.at(21)));
	transitions[30].insert(make_pair(Symbole::F, etats.at(39)));

	// transitions[31] reste vide
	// transitions[32] reste vide

	transitions[33].insert(make_pair(Symbole::pf, etats.at(40)));
	transitions[33].insert(make_pair(Symbole::opA, etats.at(27)));
	transitions[33].insert(make_pair(Symbole::pl, etats.at(28)));
	transitions[33].insert(make_pair(Symbole::mn, etats.at(29)));

	transitions[34].insert(make_pair(Symbole::opA, etats.at(27)));
	transitions[34].insert(make_pair(Symbole::pl, etats.at(28)));
	transitions[34].insert(make_pair(Symbole::mn, etats.at(29)));

	// transitions[35] reste vide

	transitions[36].insert(make_pair(Symbole::eq, etats.at(41)));

	// transitions[37] reste vide

	transitions[38].insert(make_pair(Symbole::opM, etats.at(30)));
	transitions[38].insert(make_pair(Symbole::mul, etats.at(31)));
	transitions[38].insert(make_pair(Symbole::divi, etats.at(32)));

	// transitions[39] reste vide
	// transitions[40] reste vide

	transitions[41].insert(make_pair(Symbole::val, etats.at(42)));

	// transitions[42] reste vide

	// Ajoutons-les dans m_transitions

	for(int i = 0; i < transitions.size(); i++) {
		m_transitions.insert(make_pair(etats[i], transitions[i]));
	}

	return m_transitions;

}
