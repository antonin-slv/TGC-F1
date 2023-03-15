#ifndef VOITURE_H
#define VOITURE_H

#include "Moteur.h"
#include "Roues.h"
#include <iostream>
#include <math.h>
#include "Physique.h"
#include "Vecteur.h"

using namespace std;

class Voiture {

    private:

        Moteur * mot;
        Roues * roue;

        Vecteur position;
        Vecteur hitbox;

        float acceleration;
        float vitesse;
        float angle;

        //!!la largeur et longueur sont la moitié de leur taille réelle -> calcul plus simple
        float poids, coef_aero;

    public:

        Voiture();
        Voiture(const Moteur & m,const Roues & r, float poi, float coef,float largeur,float longu, float orient=M_PI/2, float vit=0, float x=0, float y=0, float acc=0);
        Voiture(const Voiture & V);
        ~Voiture();

        Moteur * getMoteur() const;
        Roues * getRoues() const;
        float getVitesse() const;
        float getAngle() const;
        float getPoids() const;
        float getCoefAero() const;
        float getX() const;
        float getY() const;
        Vecteur getPos() const;

        Vecteur getHitbox() const;
        float getLargeur() const;
        float getLongueur() const;


        //fait accélérer la voiture pendant 1 seconde
        void accelerer(float dt=1);
        void ralentir(float dt=1);
        void freiner(float dt=1);
        //fait tourner la voiture d'un certain angle par seconde
        void tourner_g(float dt=1);
        void tourner_d(float dt=1);

    private :
        
        void tourner_var(float angle_roue_rad,float dt=1);
        
        //met a jour l'acceleration dt : temps d'acc, theta : proportion de la puissance usitée
        void calculAcc(float dt=1,float theta=1);
        //met à jour la vitesse fct de l'acceleration
        void calculVitesse(float dt=1);
        //change les coordonnées de la voiture
        void calculPosition(float dt=1);
        void calculPosition_precis(float dt=1);
};

#endif