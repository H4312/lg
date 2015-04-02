#include <iostream>
#include "Automate.h"

class Automate;

using namespace std;

int main(int argc, char** argv)
{
    Automate automate;
    //automate.lecture(argv[argc - 1]);
    automate.lecture("/home/jeremy/LG/bin/Debug/test.txt");
    Symbole* p = automate.analyser();
    TableSymbole table;
    p->eval(&table);
    p->exec(&table);


    /*
    Lexer lexer;
    lexer.openFile("/home/jeremy/LG/bin/Debug/test.txt");
    lexer.splitFileBySym();
    Symbole* s1 = lexer.readNext();
    Symbole* s2 = lexer.readNext();
    Symbole* s3 = lexer.readNext();
    cout<<s1->getType()<<"  "<<s2->getType()<<"     "<<s3->getType();
     */
    return 0;
}
