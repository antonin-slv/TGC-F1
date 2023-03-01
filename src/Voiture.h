#ifndef VOITURE_H
#define VOITURE_H

#include "Moteur.h"
#include "Roues.h"
#include <iostream>
using namespace std;

class Voiture {
    private:
        Moteur * mot;
        Roues * roue;
        float vitesse, orientation, poids, coef_aero;
    public:
        Voiture(const Moteur & m,const Roues & r, float vit, float orient, float poi, float coef);
        ~Voiture();
        float claculAcceleration();
        Moteur * getMoteur();
        Roues * getRoues();
};

#endif