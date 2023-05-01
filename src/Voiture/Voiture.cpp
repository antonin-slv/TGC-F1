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
    action=V.action;

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

float Voiture::getAcceleration() const { return acceleration; }

float Voiture::getVitesse() const { return vitesse; }

float Voiture::getAngle() const { return angle; }

float Voiture::getPoids() const { return poids; }

float Voiture::getCoefAero() const { return coef_aero; }

Vecteur Voiture::getHitbox() const { return hitbox; }

Vecteur Voiture::getPos() const { return position; }

void Voiture::crash(Vecteur diff, float anglemur)
{   
    vitesse = vitesse * cos(anglemur - angle);
    position = position - diff*0.1;
    angle = anglemur + M_PI - angle;
}



//des fonctions mieux ?

void Voiture::calculVitesse(float dt)
{
    vitesse = calculVitesse_P(vitesse,acceleration,dt);
}

void Voiture::calculPosition_precis(float dt)
{
    calculCoordonnee_precise(position.x,position.y,angle,vitesse,acceleration,dt);
}


void Voiture::tourner_var(float angle_roue_rad, float dt)
{   angle += dt * sqrt(abs(vitesse)) * angle_roue_rad / 4;
    if (angle > M_PI) angle -= 2*M_PI;
    else if (angle < -M_PI) angle += 2*M_PI;
}

void Voiture::tourner_g(float dt) { tourner_var(-1.5,dt); }

void Voiture::tourner_d(float dt) { tourner_var(1.5,dt); }

void Voiture::avancer(float portion)
{
    
    if (vitesse < 0)
    {   new_ralentir();
        acceleration *= 2;
        acceleration += 3 * portion * mot.getPuissance()/poids;
    }
    else acceleration = mot.getPuissance()*portion/poids-coef_aero*vitesse*vitesse/100;
}


void Voiture::new_freiner(float proportion)
{   
   
    if (vitesse > 0)
    {   new_ralentir();
        acceleration -= 3*proportion * mot.getPuissance()/poids;
    }
    else acceleration = -proportion*mot.getPuissance()/poids-coef_aero*abs(vitesse)*vitesse/25;

}

void Voiture::new_ralentir(float dt)
{
    acceleration = -coef_aero*abs(vitesse)*vitesse/50;
    if (vitesse > 3) acceleration-=2;
    else if (vitesse < -3) acceleration+=2;
    else{
        acceleration = 0;
        vitesse /= 1+dt*2;
        
    }   

}

void Voiture::update(float dt)
{   acceleration = 0;
    if (action.freine) new_freiner(1);
    else if (action.accelere) avancer(1);
    else new_ralentir(dt);
    if (action.gauche) tourner_g(dt);
    if (action.droite) tourner_d(dt);

    calculPosition_precis(dt);
    calculVitesse(dt);
}

void Voiture::on_grass(float dt)
{
    vitesse /= 1+dt;
}

void Voiture::setRotation(float angle_)
{
    angle = angle_;
}

void Voiture::setPos(Vecteur pos_)
{
    position = pos_;
}
void Voiture::setHitbox(Vecteur hitbox_)
{
    hitbox = hitbox_;
}

void Voiture::passer_checkpoint(bool arrivee)
{   
    if (arrivée) numero_checkpoint = -1;
    else numero_checkpoint++;
}

int Voiture::getCheckpoint() const
{
    return numero_checkpoint;
}

void Voiture::restart(Vecteur pos_, float angle_)
{
    position = pos_;
    angle = angle_;
    vitesse = 0;
    acceleration = 0;
    numero_checkpoint = -1;
}