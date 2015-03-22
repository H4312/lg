#include "Automate.h"

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

void Automate::decalage(Symbole *sym, Etat *etat) {

}
