#include "Lexer.h"
#include <fstream>
#include <iostream>

Lexer::Lexer()
{
    matchingMap.emplace(matchingMap.end(), "+", NULL);
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
    matchingMap.emplace(matchingMap.end(), "[a-Z][a-Z0-9]*", NULL); //id
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

void Lexer::splitFileBySym() {
    char c;
    string current;
    bool affsym = false;

    while(this->file.get(c)) {
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
        }
        else
        {
            current += c;
        }
    }
}

void Lexer::closeFile()
{
    this->file.close();
}

Symbole *Lexer::readCurrent() {

    cout << current_line << endl;
    return NULL;
}

Symbole *Lexer::readNext() {
    cursorNext();
    return NULL;
}

bool Lexer::cursorNext() {
    /*
    * We take the next char or the first char of the
    * next line if we are at the end of the line
    */
    if(current_char_number >= current_line.length()) {
        if(getline(this->file, current_line)) {
            current_line_number++;
            current_char_number = 0;
        } else {
            cout << "Fin du fichier" << endl;
            return false;
        }
    } else {
        current_char_number++;
    }
    return true;
}

string Lexer::readSymbole() {
    while(this->current_line.length());
}

void Lexer::DisplaySplittedFile() {
    for(auto& elem : *this->splittedFile) {
        cout << elem + "| " << endl;
    }
}

bool Lexer::isFileOpen() {
    return this->file.is_open();
}
