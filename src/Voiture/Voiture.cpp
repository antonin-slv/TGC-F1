#include "Moteur.h"
#include "Roues.h"
#include "Voiture.h"
#include <iostream>
#include "Physique.h"
#include <math.h>
#include "Vecteur.h"

using namespace std;

Voiture::Voiture()
{
    mot = new Moteur();
    roue = new Roues();
    vitesse = Vecteur();
    position = Vecteur();
    poids = 796;
    coef_aero = 0.14;
    acceleration=0;
    cout << "Construct voiture def" << endl;
}

Voiture::Voiture(const Moteur & M, const Roues & R, float poid, float coef, float larg, float longu, float orient, float vit, float x, float y, float acc){
    
    mot = new Moteur(M);
    roue = new Roues(R);
    vitesse=Vecteur();
    vitesse.setVecteur(vit,orient);
    position=Vecteur(x,y);
    poids = poid;
    largeur=larg;
    longueur=longu;
    coef_aero = coef;
    acceleration=acc;
    
    cout << "Construct voiture" << endl;
}

Voiture::Voiture(const Voiture & V){
    mot = new Moteur(*V.mot);
    roue = new Roues(*V.roue);

    vitesse = V.vitesse;
    position = V.position;

    poids = V.poids;
    coef_aero = V.coef_aero;
    largeur=V.largeur;
    longueur=V.longueur;
    acceleration=V.acceleration;
    cout << "Construct voiture" << endl;
}

Voiture::~Voiture(){
    if (mot != nullptr) delete mot;
    if (roue != nullptr) delete roue;
    cout << "Destruct voiture" << endl;
}

Moteur * Voiture::getMoteur() const { return mot; }

Roues * Voiture::getRoues() const { return roue; }

float Voiture::getVitesse() const { return vitesse.getNorme(); }

float Voiture::getAngle() const { return vitesse.getRotation(); }

float Voiture::getPoids() const { return poids; }

float Voiture::getCoefAero() const { return coef_aero; }

float Voiture::getX() const { return position.x; }

float Voiture::getY() const { return position.y; }

float Voiture::getLargeur() const { return largeur; }

float Voiture::getLongueur() const { return longueur; }

void Voiture::calculAcc(float dt,float theta)
{
    acceleration = calculAcceleration(vitesse.getNorme(),poids,coef_aero,mot->getPuissance()*theta);
}

void Voiture::calculVitesse(float dt)
{
    vitesse.setVecteur(
        calculVitesse_P(vitesse.getNorme(),acceleration,dt),
        vitesse.getRotation()
        );
}

void Voiture::calculPosition(float dt){
    calculCoordonnee(position.x,position.y,vitesse.getRotation(),vitesse.getNorme(),dt);
}

void Voiture::calculPosition_precis(float dt)
{
    calculCoordonnee_precise(position.x,position.y,vitesse.getRotation(),vitesse.getNorme(),acceleration,dt);
}

void Voiture::tourner_var(float angle_roue_rad, float dt)
{    if ( abs(vitesse.getNorme()) > 1) vitesse.tourner(angle_roue_rad*dt);
    else vitesse.tourner(dt * vitesse.getNorme() * angle_roue_rad);
    //en principe il faudrait prendre la vitesse en compte, mais ça sert pour limiter la rotation de la voiture à haute vitesse
    //on a l'impression que la voiture tourne toujours de la même façon, mais les roues non (l'angle est moins grand quand on roule vite)
    //le else est un ajout pour que la voiture ne tourne pas à l'arrêt
}

void Voiture::tourner_g(float dt) { tourner_var(0.6,dt); }

void Voiture::tourner_d(float dt) { tourner_var(-0.6,dt); }

void Voiture::accelerer(float dt)
{   calculAcc(dt,1);
    calculPosition_precis(dt);
    calculVitesse(dt);
}

void Voiture::ralentir(float dt)
{   calculAcc(dt,0.1);
    calculPosition_precis(dt);
    calculVitesse(dt);
}

void Voiture::freiner(float dt)
{   if (vitesse.getNorme() > 0) calculAcc(dt,-vitesse.getNorme()/150-1);
    else
    {   acceleration = calculAcceleration(vitesse.getNorme(),poids,coef_aero*10,-mot->getPuissance()/4);
        //if (vitesse < -40) vitesse = -40;
    }
    calculPosition_precis(dt);
    calculVitesse(dt);
    //if (vitesse < 0.1) vitesse = 0;
}