#ifndef SYMBOLE_H
#define SYMBOLE_H
#include <string>

using namespace std;


class Symbole
{
    public:
        Symbole(int id) : ident(id) {}
        virtual ~Symbole();
        virtual bool eval(string s){return false;}
        operator int() const {return ident;}
    protected:
        int ident;
    private:
};

#endif // SYMBOLE_H
