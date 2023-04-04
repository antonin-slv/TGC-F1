#include "Moteur.h"
#include "Roues.h"
#include "Voiture.h"
#include <iostream>
#include "Physique.h"
#include <math.h>
#include "Vecteur.h"

using namespace std;

/**
 * @brief Constructeur par défaut de Voiture, ne prends aucun paramètre
 * 
 */
Voiture::Voiture()
{
    mot = Moteur();
    roue = Roues();
    vitesse = 0;
    angle = 0;
    position = Vecteur(10,10);
    hitbox = Vecteur(2.5,1);
    poids = 796;
    coef_aero = 0.14;
    acceleration=0;
    //cout << "Construct voiture def" << endl;
}

/**
 * @brief Construct a new Voiture:: Voiture object
 * 
 * @param M 
 * @param R 
 * @param poid 
 * @param coef 
 * @param larg 
 * @param longu 
 * @param orient 
 * @param vit 
 * @param x 
 * @param y 
 * @param acc 
 */
Voiture::Voiture(const Moteur & M, const Roues & R, float poid, float coef, float larg, float longu, float orient, float vit, float x, float y, float acc){
    
    mot = Moteur(M);
    roue = Roues(R);
    vitesse=vit;
    angle=orient;
    position=Vecteur(x,y);
    hitbox=Vecteur(larg,longu);
    poids = poid;
    coef_aero = coef;
    acceleration=acc;
    
    //cout << "Construct voiture" << endl;
}

Voiture::Voiture(const Voiture & V){
    mot =V.mot;
    roue = V.roue;

    vitesse = V.vitesse;
    angle = V.angle;
    position = V.position;

    poids = V.poids;
    coef_aero = V.coef_aero;
    hitbox = V.hitbox;
    acceleration=V.acceleration;
    //cout << "Construct voiture" << endl;
}
Voiture::~Voiture(){
    //cout << "Destruct voiture" << endl;
}
/*
bool Voiture::chargerJSON(const char * obj)
{   
    if (obj.type() != json::value_t::object)
    {
        cout << "voiture corrompue" << endl;
        return false;
    }
    if (obj["x"].type() == json::value_t::null) pos.x=0;
    else pos.x = obj["x"];
    if (obj["y"].type() == json::value_t::null) pos.y=0;
    else pos.y = obj["y"];
    if (obj["angle"].type() == json::value_t::null) angle=0;
    else angle = obj["angle"];
    if (obj["vitesse"].type() == json::value_t::null) vitesse=0;
    else vitesse = obj["vitesse"];
    if (obj["l"].type() == json::value_t::null) hitbox.x=0;
    else hitbox.x = obj["l"];
    if (obj["L"].type() == json::value_t::null) hitbox.y=0;
    else hitbox.y = obj["L"];
    if (obj["poids"].type() == json::value_t::null) poids=1000;
    else poids = obj["poids"];
    if (obj["coef_aero"].type() == json::value_t::null) coef_aero=1;
    else coef_aero = obj["coef_aero"];
    if (obj["acceleration"].type() == json::value_t::null) acceleration=0;
    else acceleration = obj["acceleration"];

    if(obj["Puissance"].type() == json::value_t::null) mot = Moteur();
    else mot = Moteur("basic",obj["Puissance"]);
    if(obj["Grip"].type() == json::value_t::null) roue = Roues();
    else roue = Roues("basic",obj["Grip"]);
    return true;
}
*/


const Moteur & Voiture::getMoteur() const { return mot; }

const Roues & Voiture::getRoues() const { return roue; }

float Voiture::getVitesse() const { return vitesse; }

float Voiture::getAngle() const { return angle; }

float Voiture::getPoids() const { return poids; }

float Voiture::getCoefAero() const { return coef_aero; }

float Voiture::getX() const { return position.x; }

float Voiture::getY() const { return position.y; }

float Voiture::getLargeur() const { return hitbox.y; }

float Voiture::getLongueur() const { return hitbox.x; }

Vecteur Voiture::getHitbox() const { return hitbox; }

Vecteur Voiture::getPos() const { return position; }


void Voiture::calculAcc(float dt,float theta)
{
    acceleration = calculAcceleration(vitesse,poids,coef_aero,mot.getPuissance()*theta);
}

void Voiture::calculVitesse(float dt)
{
    vitesse = calculVitesse_P(vitesse,acceleration,dt);
}

void Voiture::calculPosition_precis(float dt)
{
    calculCoordonnee_precise(position.x,position.y,angle,vitesse,acceleration,dt);
}


void Voiture::tourner_var(float angle_roue_rad, float dt)
{    if ( abs(vitesse) > 1) angle += angle_roue_rad*dt;
    else angle += dt * vitesse * angle_roue_rad;
    //en principe il faudrait prendre la vitesse en compte, mais ça sert pour limiter la rotation de la voiture à haute vitesse
    //on a l'impression que la voiture tourne toujours de la même façon, mais les roues non (l'angle est moins grand quand on roule vite)
    //le else est un ajout pour que la voiture ne tourne pas à l'arrêt
}

void Voiture::tourner_g(float dt) { tourner_var(-1.5,dt); }

void Voiture::tourner_d(float dt) { tourner_var(1.5,dt); }


void Voiture::accelerer(float dt)
{   calculAcc(dt,1);
    calculPosition_precis(dt);
    calculVitesse(dt);
}

void Voiture::ralentir(float dt)
{   calculAcc(dt,0);
    calculPosition_precis(dt);
    calculVitesse(dt);
}

void Voiture::freiner(float dt)
{   if (vitesse > 0) acceleration = calculAcceleration(vitesse,poids,coef_aero*10,-mot.getPuissance());
    else
    {   acceleration = calculAcceleration(vitesse,poids,coef_aero*10,-mot.getPuissance()/4);
        if (vitesse < -40) vitesse = -40;
    }
    calculPosition_precis(dt);
    calculVitesse(dt);
    //if (vitesse < 0.1) vitesse = 0;
}

void Voiture::crash(Vecteur diff, float anglemur)
{   
    vitesse = vitesse * cos(anglemur - angle);
    position = position - diff*0.1;
    angle = anglemur + M_PI - angle;
}



//des fonctions mieux ?
void Voiture::avancer(float portion)
{
    acceleration = calculAcceleration(0,poids,0,mot.getPuissance()*portion);
}


void Voiture::new_freiner(float proportion)
{   if (vitesse > 0)
    {   acceleration = calculAcceleration(0,poids,0,-proportion*mot.getPuissance());
    }
    else
    {   acceleration = calculAcceleration(0,poids,0,-proportion*mot.getPuissance()/2);
        if (vitesse < -40) vitesse = -40;
    }
}

void Voiture::new_ralentir(float dt)
{   acceleration -= calculAcceleration(vitesse,poids,coef_aero,0);
    vitesse = calculVitesse_P(vitesse,acceleration,dt);
}

void Voiture::calculPosition(float dt){
    calculCoordonnee(position.x,position.y,angle,vitesse,dt);
}