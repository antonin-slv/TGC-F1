#ifndef VOITURE_H
#define VOITURE_H

#include "Moteur.h"
#include "Roues.h"
#include <iostream>
using namespace std;

class Voiture{
    private:
        Moteur M;
        Roues R;
        float vitesse, orientation, poids, coef_aero;
};

#endif