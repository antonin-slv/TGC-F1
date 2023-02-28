#include "Moteur.h"
#include "Roues.h"
#include "Voiture.h"
#include <iostream>
using namespace std;

Voiture::Voiture(const Moteur & M, const Roues & R, float v, float o, float p, float coef){
    
    mot = new Moteur(M);
    roue = new Roues(R);

    vitesse = v;
    orientation = o;
    poids = p;
    coef_aero = coef;
    cout << "Construct voiture" << endl;
}
