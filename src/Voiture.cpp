#include "Moteur.h"
#include "Roues.h"
#include "Voiture.h"
#include <iostream>
using namespace std;

Voiture::Voiture(const Moteur & M, const Roues & R, float poid, float coef, float orient, float vit){
    
    mot = new Moteur(M);
    roue = new Roues(R);

    vitesse = vit;
    angle= orient;
    poids = poid;
    coef_aero = coef;
    
    cout << "Construct voiture" << endl;
}

Voiture::~Voiture(){
    if (mot != nullptr) delete mot;
    if (roue != nullptr) delete roue;
    cout << "Destruct voiture" << endl;
}

Moteur * Voiture::getMoteur(){  return mot; }

Roues * Voiture::getRoues(){    return roue; }

float Voiture::getVitesse(){    return vitesse; }

float Voiture::getAngle(){  return angle; }

float Voiture::getPoids(){  return poids; }

float Voiture::getCoefAero(){   return coef_aero; }

float Voiture::claculAcceleration(){
    return mot->getPuissance()/(poids * (1 + coef_aero));
}


