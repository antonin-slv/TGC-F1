#ifndef MOTEUR_H
#define MOTEUR_H

#include <iostream>
#include <string>

using namespace std;

class Moteur{

    private:

        string nom;
        int puissance;

    public:

        Moteur();
        Moteur(string n,int p);
        Moteur(const Moteur & M);
        

        
        string getNom();
        int getPuissance();

};


#endif