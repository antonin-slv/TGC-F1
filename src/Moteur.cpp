#include "Moteur.h"
#include <iostream>
#include <string>
using namespace std;

Moteur::Moteur(){
    nom = string("");
    puissance = 0;
    cout << "Construct moteur vide";
}
Moteur::Moteur(string n,int p){
    nom = n;
    puissance = p;
    cout << "Construct moteur";
}

Moteur::Moteur(const Moteur & M){
    nom = M.nom;
    puissance = M.puissance;
    cout << "Construct moteur copie";
}
