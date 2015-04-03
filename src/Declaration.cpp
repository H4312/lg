#include "Declaration.h"

using namespace std;

Declaration::Declaration()
{
	
}

Declaration::Declaration(string nom)
{
    this->nom = nom ;
}

std::string Declaration::getNom()
{
	return nom;
}

void Declaration::setNom(string nom)
{
	this->nom = nom;
}

double Declaration::getVal()
{
	return val;
}

void Declaration::setVal(double val)
{
	this->val = val ;
}