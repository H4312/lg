#ifndef SYMBOLE_H
#define SYMBOLE_H
#include <string>

using namespace std;


class Symbole
{
    public:
        Symbole();
        virtual ~Symbole();
        virtual bool eval(string s) = 0;
    protected:
    private:
};

#endif // SYMBOLE_H
