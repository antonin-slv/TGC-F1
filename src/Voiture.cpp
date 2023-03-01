#include "Moteur.h"
#include "Roues.h"
#include "Voiture.h"
#include <iostream>
using namespace std;

Voiture::Voiture(const Moteur & M, const Roues & R, float vit, float orient, float poi, float coef){
    
    mot = new Moteur(M);
    roue = new Roues(R);

    vitesse = vit;
    orientation = orient;
    poids = poi;
    coef_aero = coef;
    cout << "Construct voiture" << endl;
}

Voiture::~Voiture(){
    delete mot;
    delete roue;
    cout << "Destruct voiture" << endl;
}

float Voiture::claculAcceleration(){
    return mot->getPuissance()/(poids * (1 + coef_aero));
}

Moteur * Voiture::getMoteur(){
    return mot;
}

Roues * Voiture::getRoues(){
    return roue;
}