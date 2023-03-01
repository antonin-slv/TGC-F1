#include "Moteur.h"
#include "Roues.h"
#include "Voiture.h"
#include <iostream>
#include "Physique.h"

using namespace std;

Voiture::Voiture(const Moteur & M, const Roues & R, float poid, float coef, float orient, float vit, float x, float y){
    
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

Moteur * Voiture::getMoteur(){ return mot; }

Roues * Voiture::getRoues(){ return roue; }

float Voiture::getVitesse(){ return vitesse; }

float Voiture::getAngle(){ return angle; }

float Voiture::getPoids(){ return poids; }

float Voiture::getCoefAero(){ return coef_aero; }

float Voiture::getX(){ return x; }

float Voiture::getY(){ return y; }

void Voiture::accelerer_sur(float dt){
    float acc = calculAcceleration(vitesse,poids,coef_aero,mot->getPuissance());
    vitesse = calculVitesse(vitesse, acc, dt);
}

void Voiture::calculPosition(float dt){
    calculCoordonnee(x,y,angle,vitesse,dt);
}


