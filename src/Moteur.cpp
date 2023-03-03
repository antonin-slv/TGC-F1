#include "Moteur.h"
#include <iostream>
#include <string>
using namespace std;

Moteur::Moteur(){
    nom = string("defaut");
    puissance = 1000*2.7*3.5;
    cout << "Construct moteur vide" << endl;
}
Moteur::Moteur(string n,int p){
    nom = n;
    puissance = p;
    cout << "Construct moteur" << endl;
}

Moteur::Moteur(const Moteur & M){
    nom = M.nom;
    puissance = M.puissance;
    cout << "Construct moteur copie" << endl;
}

string Moteur::getNom(){
    return nom;
}

int Moteur::getPuissance(){
    return puissance;
}