#include "Moteur.h"
#include "Roues.h"
#include "Voiture.h"
#include <iostream>
#include "Physique.h"

using namespace std;

Voiture::Voiture()
{
    mot = new Moteur();
    roue = new Roues();
    vitesse = 0;
    angle= 0;
    poids = 796;
    coef_aero = 0.14;
    acceleration=0;
    cout << "Construct voiture def" << endl;
}

Voiture::Voiture(const Moteur & M, const Roues & R, float poid, float coef, float orient, float vit, float x, float y, float acc){
    
    mot = new Moteur(M);
    roue = new Roues(R);

    vitesse = vit;
    angle= orient;
    poids = poid;
    coef_aero = coef;
    acceleration=acc;
    
    cout << "Construct voiture" << endl;
}

Voiture::Voiture(const Voiture & V){
    mot = new Moteur(*V.mot);
    roue = new Roues(*V.roue);

    vitesse = V.vitesse;
    angle= V.angle;
    poids = V.poids;
    coef_aero = V.coef_aero;
    acceleration=V.acceleration;
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
{   angle += dt * angle_roue_rad / 2;
    //en principe il faudrait prendre la vitesse en compte, mais ça sert pour limiter la rotation de la voiture à haute vitesse
    //on a l'impression que la voiture tourne toujours de la même façon, mais les roues non (l'angle est moins grand quand on roule vite) 
    if (angle > 2*M_PI) angle -= 2*M_PI;
    if (angle < -2*M_PI) angle += 2*M_PI;
}
