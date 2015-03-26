w#include "Automate.h"
#include "Symbole.h"

using namespace std;

Automate::Automate()
{
    //ctor
}

Automate::~Automate()
{
    //dtor
}

void Automate::lecture(const char* filename)
{
    lexer.readCurrent();
}

void Automate::analyser()
{
    Etat* n = m_transitions.find(m_etats.top())->second.find(currentSym->getType())->second;

    if (n!=NULL)
    {
        decalage(n);
    }
    else
    {
        reduire();
    }
}

void Automate::decalage(Etat *etat)
{
    m_etats.push(etat);
    m_symboles.push(currentSym);
    currentSym=NULL;
}

void Automate::reduire()
{
    Etat* etat = m_etats.top();
    Symbole* s = new Symbole(etat->getGauche());
    for(int i = 0 ; i < etat->getNbr() ; i++ )
    {
        s->ajouterFils(m_symboles.top());
        m_etats.pop();
        m_symboles.pop();
    }
    m_symboles.push(s);
}

map<Etat*, map<TYPE, Etat*> > Automate::initMap() {
	const int nombreEtats = 43;
			
	// Map pour les transitions
	map<Etat*, map<TYPE, Etat*> > m_transitions;
		
	// Initialiser un vector avec 43 pour les etats
	vector<Etat*> etats(nombreEtats, NULL);
		
	map<TYPE, Etat*> transitions_initialize;
	transitions_initialize.insert(make_pair(P, etats.at(1)));
		
	// Initialiser un vector avec 43 pour les transitions
	// et ajouter les transitions correspondantes
	// (Attention: etats.at(0) et E0 égal à l'état1 dans l'automate)
	vector< map<TYPE, Etat*> > transitions(nombreEtats, transitions_initialize);
		
	transitions[0].insert(make_pair(BD, etats.at(1)));
		
	transitions[1].insert(make_pair(BI, etats.at(2)));
	transitions[1].insert(make_pair(D, etats.at(3)));
	transitions[1].insert(make_pair(var, etats.at(4)));
	transitions[1].insert(make_pair(cons, etats.at(5)));
	
	transitions[2].insert(make_pair(ecrire, etats.at(7)));
	transitions[2].insert(make_pair(lire, etats.at(8)));
	transitions[2].insert(make_pair(id, etats.at(10)));
		
	transitions[3].insert(make_pair(pv, etats.at(10)));
		
	transitions[4].insert(make_pair(L, etats.at(11)));
	transitions[4].insert(make_pair(id, etats.at(12)));
		
	transitions[5].insert(make_pair(C, etats.at(13)));
	transitions[5].insert(make_pair(id, etats.at(14)));
		
	transitions[6].insert(make_pair(pv, etats.at(15)));
		
	transitions[7].insert(make_pair(O, etats.at(16)));
	transitions[7].insert(make_pair(T, etats.at(17)));
	transitions[7].insert(make_pair(F, etats.at(18)));
	transitions[7].insert(make_pair(id, etats.at(19)));
	transitions[7].insert(make_pair(val, etats.at(20)));
	transitions[7].insert(make_pair(po, etats.at(21)));
	
	transitions[8].insert(make_pair(id, etats.at(22)));
		
	transitions[9].insert(make_pair(aff, etats.at(23)));
		
	// transitions[10] reste vide
		
	transitions[11].insert(make_pair(v, etats.at(24)));
		
	// transitions[12] reste vide
		
	transitions[13].insert(make_pair(v, etats.at(25)));
		
	transitions[14].insert(make_pair(eq, etats.at(26)));
			
	// transitions[15] reste vide
		
	transitions[16].insert(make_pair(opA, etats.at(27)));
	transitions[16].insert(make_pair(pl, etats.at(28)));
	transitions[16].insert(make_pair(mn, etats.at(29)));
		
	transitions[17].insert(make_pair(opM, etats.at(30)));
	transitions[17].insert(make_pair(mul, etats.at(31)));
	transitions[17].insert(make_pair(opA, etats.at(32)));
		
	// transitions[18] reste vide
	// transitions[19] reste vide
	// transitions[20] reste vide
		
	transitions[21].insert(make_pair(T, etats.at(17)));
	transitions[21].insert(make_pair(F, etats.at(18)));
	transitions[21].insert(make_pair(id, etats.at(19)));
	transitions[21].insert(make_pair(val, etats.at(20)));

	// transitions[22] reste vide
		
	transitions[23].insert(make_pair(T, etats.at(17)));
	transitions[23].insert(make_pair(F, etats.at(18)));
	transitions[23].insert(make_pair(id, etats.at(19)));
	transitions[23].insert(make_pair(val, etats.at(20)));
	transitions[23].insert(make_pair(po, etats.at(21)));
	transitions[23].insert(make_pair(O, etats.at(34)));
		
	transitions[24].insert(make_pair(id, etats.at(35)));
		
	transitions[25].insert(make_pair(id, etats.at(36)));
		
	transitions[26].insert(make_pair(val, etats.at(37)));
		
	transitions[26].insert(make_pair(T, etats.at(38)));
	transitions[26].insert(make_pair(F, etats.at(18)));
	transitions[26].insert(make_pair(id, etats.at(19)));
	transitions[26].insert(make_pair(val, etats.at(20)));
	transitions[26].insert(make_pair(po, etats.at(21)));
		
	// transitions[28] reste vide
	// transitions[29] reste vide
			
	transitions[30].insert(make_pair(id, etats.at(19)));
	transitions[30].insert(make_pair(val, etats.at(20)));
	transitions[30].insert(make_pair(po, etats.at(21)));
	transitions[30].insert(make_pair(F, etats.at(39)));
		
	// transitions[31] reste vide
	// transitions[32] reste vide
		
	transitions[33].insert(make_pair(pf, etats.at(40)));
	transitions[33].insert(make_pair(opA, etats.at(27)));
	transitions[33].insert(make_pair(pl, etats.at(28)));
	transitions[33].insert(make_pair(mn, etats.at(29)));
		
	transitions[34].insert(make_pair(opA, etats.at(27)));
	transitions[34].insert(make_pair(pl, etats.at(28)));
	transitions[34].insert(make_pair(mn, etats.at(29)));
		
	// transitions[35] reste vide
		
	transitions[36].insert(make_pair(eq, etats.at(41)));
		
	// transitions[37] reste vide
		
	transitions[38].insert(make_pair(opM, etats.at(30)));
	transitions[38].insert(make_pair(mul, etats.at(31)));
	transitions[38].insert(make_pair(divi, etats.at(32)));
		
	// transitions[39] reste vide
	// transitions[40] reste vide
		
	transitions[41].insert(make_pair(val, etats.at(42)));
		
	// transitions[42] reste vide
		
	// Ajoutons-les dans m_transitions
	for(int i = 0; i < m_transitions.size(); i++) {
		m_transitions.insert(make_pair(etats[i], transitions[i]));
	}
	
	return m_transitions;

}
