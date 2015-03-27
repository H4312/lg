#include "TableSymbole.h"

using namespace std;

////////////////////////////////////////////////////////////////////////
// Name:       TableSmybole::AjouterDeclaration(Declaration declaration)
// Purpose:    Implementation of TableSmybole::AjouterDeclaration()
// Parameters:
// - declaration
// Return:     bool
////////////////////////////////////////////////////////////////////////

Declaration::Declaration()
{
	
}

Declaration::Declaration(string id)
{
    this->id = id ;
}

std::string Declaration::getNom(){
	return id;
}

void Declaration::setNom(string nom){
	this->id = nom;
}

double Declaration::getVal(){
	return val;
}

void Declaration::setVal(double val){
	this->val = val ;
}