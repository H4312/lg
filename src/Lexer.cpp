#include "Lexer.h"
#include "Symbole.h"
#include <iostream>

Lexer::Lexer()
{
   /* matchingMap.emplace(matchingMap.end(), "+", NULL);
    matchingMap.emplace(matchingMap.end(), "-", NULL);
    matchingMap.emplace(matchingMap.end(), "*", NULL);
    matchingMap.emplace(matchingMap.end(), "/", NULL);
    matchingMap.emplace(matchingMap.end(), ":=", NULL);
    matchingMap.emplace(matchingMap.end(), "=", NULL);
    matchingMap.emplace(matchingMap.end(), ";", NULL);
    matchingMap.emplace(matchingMap.end(), ")", NULL);
    matchingMap.emplace(matchingMap.end(), "(", NULL);
    matchingMap.emplace(matchingMap.end(), "const", NULL); //const
    matchingMap.emplace(matchingMap.end(), "var", NULL); //var

    matchingMap.emplace(matchingMap.end(), "(\\+|-)?[[:digit:]]+", NULL); //Integer
    matchingMap.emplace(matchingMap.end(), "[a-Z][a-Z0-9]*", NULL); //id*/
}

Lexer::~Lexer()
{
    delete this->splittedFile;
}

bool Lexer::openFile(char *filename)
{
    this->file.open(filename);
    if (this->file.is_open())
    {
        return true;
    }
    else
    {
        cerr << "Unable to open file";
        return false;
    }
}

vector<string> * Lexer::splitFileBySym() {
    char c;
    string current;
    bool affsym = false;
    int num_line = 1;
    int num_char = 0;

    while(this->file.get(c)) {
        if(c == '\n') {
            num_line++;
            num_char = 0;
        } else {
            num_char++;
        }
        if(
                c == '+' || c == '-' || c == '*'||
                c == '/' || c == ';' ||
                c == '=' && !affsym || c == ',')
        {
            if(current.length() > 0)
            {
                splittedFile->push_back(current);
                current = "";
            }
            string s;
            s = s + c;
            this->splittedFile->push_back(s);
        }
        else if (c == '=' && affsym)
        {
            // Symbole affectation
            splittedFile->push_back(":=");
            affsym = false;
        }
        else if ( (c == ' ' || c == '\n') )
        {
            // Espace ou saut de ligne

            if(current.length() > 0) {
                splittedFile->push_back(current);
                current = "";
            }
        }
        else if( c == ':')
        {
            // Debut de reconnaissance d'un symbole d'affectation
            affsym = true;

            if(current.length() > 0) {
                splittedFile->push_back(current);
                current="";
            }

        }
        else if(isalnum(c))
        {
            current += c;
        } else {
            cerr << "Symbole invalide ligne " << num_line << " position " << num_char << endl;
        }
    }
    splittedFile->push_back(current);

    return splittedFile;
}

void Lexer::closeFile()
{
    this->file.close();
}



Symbole *Lexer::readNext() {
    if(current_symbole >= splittedFile->size()) return 0;
    return getSymbole(splittedFile->at(current_symbole++));
}

Symbole *Lexer::sonder() {
    if(current_symbole >= splittedFile->size()) return 0;
    return getSymbole(splittedFile->at(current_symbole));
}


void Lexer::DisplaySplittedFile() {
    for(auto& elem : *this->splittedFile) {
        cout << elem + "| " << endl;
    }
}

bool Lexer::isFileOpen() {
    return this->file.is_open();
}


Symbole *Lexer::getSymbole(string str) {
    Symbole* sym = nullptr;
    if(str == "const") {
        sym = new Symbole(Symbole::cons);
    } else if(str == "var") {
        sym = new Symbole(Symbole::var);
    } else if(str == "ecrire") {
        sym = new Symbole(Symbole::ecrire);
    } else if(str == "lire") {
        sym = new Symbole(Symbole::lire);
    } else if(str == ":=") {
        sym = new Symbole(Symbole::aff);
    } else if(str == "=") {
        sym = new Symbole(Symbole::eq);
    } else if(str == "+") {
        sym = new Symbole(Symbole::pl);
    } else if(str == "-") {
        sym = new Symbole(Symbole::mn);
    } else if(str == "*") {
        sym = new Symbole(Symbole::mul);
    } else if(str == ";") {
        sym = new Symbole(Symbole::pv);
    } else if(str == ",") {
        sym = new Symbole(Symbole::v);
    } else if(str == "/") {
        sym = new Symbole(Symbole::divi);
    } else if(isOnlyDouble(str.c_str())) {
        sym = new Symbole(Symbole::val);
        sym->setValue(stod(str));
    } else if(isIdentifier(str)) {
        sym = new Symbole(Symbole::id);
        sym->setNom(str);
    }

    return sym;
}

bool Lexer::isInteger(const std::string & s)
{
    if(s.empty() || ((!isdigit(s[0])))) return false ;

    char * p ;
    strtol(s.c_str(), &p, 10) ;

    return (*p == 0) ;
}

bool Lexer::isOnlyDouble(const char* str)
{

    if(!isdigit(str[0])) return false;
    char* endptr = 0;
    strtod(str, &endptr);

    if(*endptr != '\0' || endptr == str)
        return false;
    return true;
}

bool Lexer::isIdentifier(const std::string & s) {
    if(!isalpha(s[0])) return false;
    for(int i = 1; i < s.length(); i++) {
        if(!isalnum(s[i])) return false;
    }
    return true;
}
