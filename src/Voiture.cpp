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

void Voiture::calculAcc(float dt,float teta)
{
    acceleration = calculAcceleration(vitesse,poids,coef_aero,mot->getPuissance()*teta);
}

void Voiture::calculVitesse(float dt)
{
    vitesse=calculVitesse_P(vitesse,acceleration,dt);
}

void Voiture::calculPosition(float dt){
    calculCoordonnee(x,y,angle,vitesse,dt);
}

void Voiture::calculPosition_precis(float dt)
{
    calculCoordonnee_precise(x,y,angle,vitesse,acceleration,dt);
}

void Voiture::tourner(float angle_roue_rad, float dt)
{   angle += vitesse * dt * angle_roue_rad / 5;
    if (angle > 2*M_PI) angle -= 2*M_PI;
    if (angle < -2*M_PI) angle += 2*M_PI;
}

