#include "Moteur.h"
#include <iostream>
using namespace std;

Moteur::Moteur(char n[16],int p){
    nom = n;
    puissance = p;
    cout << "Construct moteur";
}
