#ifndef VOITURE_H
#define VOITURE_H

#include "Moteur.h"
#include "Roues.h"
#include <iostream>
#include <math.h>
using namespace std;

class Voiture {

    private:

        Moteur * mot;
        Roues * roue;
        float vitesse, angle;
        float poids, coef_aero;

    public:

        Voiture(const Moteur & m,const Roues & r, float poi, float coef, float orient=M_PI/2, float vit=0);
        ~Voiture();

        Moteur * getMoteur();
        Roues * getRoues();
        float getVitesse();
        float getAngle();
        float getPoids();
        float getCoefAero();
        
        float claculAcceleration();
        void accelerer();
};

#endif