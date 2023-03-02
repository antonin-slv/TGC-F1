#ifndef VOITURE_H
#define VOITURE_H

#include "Moteur.h"
#include "Roues.h"
#include <iostream>
#include <math.h>
#include "Physique.h"

using namespace std;

class Voiture {

    private:

        Moteur * mot;
        Roues * roue;

        float vitesse, angle;
        float x,y;
        float poids, coef_aero;

    public:

        Voiture(const Moteur & m,const Roues & r, float poi, float coef, float orient=M_PI/2, float vit=0, float x=0, float y=0);
        ~Voiture();

        Moteur * getMoteur();
        Roues * getRoues();
        float getVitesse();
        float getAngle();
        float getPoids();
        float getCoefAero();
        float getX();
        float getY();

        void accelerer_sur(float dt=1);
        void calculPosition(float dt=1);

        void calculPosition_precis(float dt=1);
};

#endif