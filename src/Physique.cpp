#include <math.h>
#include "Physique.h"

/*  la puissance est en N

*/
float calculAcceleration(float vitesse, float poids, float coef_aero, float puissance){
    float a = puissance - coef_aero*vitesse*vitesse*7;
    if (poids >= 0.001) a /= poids;
    else a /= 0.001;

    return a;
}

float calculVitesse(float vitesse_init, float acceleration, float dt){
   return vitesse_init + acceleration*dt;
}


void calculCoordonnee(float & x, float & y, float angle, float vitesse, float dt){
    x=x + vitesse*cos(angle)*dt;
    y=y + vitesse*sin(angle)*dt;


}