#include "Moteur.h"
#include "Roues.h"
#include <iostream>
using namespace std;

Voiture::Voiture(Moteur M, Roues R, float v, float o, float p, float coef){
    Moteur = M;
    Roues = R;
    vitesse = v;
    orientation = o;
    poids = p;
    coef_aero = coef;
    cout << "Construct voiture";
}
