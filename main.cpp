#include <iostream>
#include "Automate.h"
#include <string.h>

using namespace std;

int main(int argc, char** argv)
{
    

    string erreurArgument = "Erreur, veuillez specifier un argument existant\nUtilisation : \n../lut [-p] [-a] [-e] [-o] source.lt \n[-p] affiche le code source reconnu \n[-a] analyse le programme de maniere statique \n[-e] execute interactivement le programme \n[-o] optimise les expressions et instructions \n";
    if(argc == 1){
        cerr << erreurArgument << endl;
        return 1;
    }
    Automate automate;
    if(!automate.lecture(argv[argc-1]))
    {
        return 1;
    }
    else automate.analyser();
    
    for(int i = 1 ; i < argc-1 ; i++) 
    {
        if(strcmp(argv[i], "-a")==0)
        {
            automate.programme->analyserStatiquement();
        }
        else if(strcmp(argv[i],"-e")==0)
        {
            automate.exec();
        }
        else if(strcmp(argv[i],"-p")==0)
        {
            cout << automate.programme->toString() << endl ;
        }
        else if(strcmp(argv[i],"-p")!=0 && strcmp(argv[i],"-e")!=0 && strcmp(argv[i], "-a")!=0)
        {
            cerr << erreurArgument << endl;
            return 1;
        }
    }
    return 0;
}
