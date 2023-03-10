#include <math.h>
#include "Physique.h"

/*  la puissance est en N

*/
float calculAcceleration(float vitesse, float poids, float coef_aero, float puissance){
    float a = puissance - coef_aero*abs(vitesse)*vitesse*6.2;
    
    
    if (poids >= 0.001) a /= poids;
    else a /= 0.001;

    return a;
}

float calculVitesse_P(float vitesse_init, float acceleration, float dt){
   return vitesse_init + acceleration*dt;
}


void calculCoordonnee(float & x, float & y, float angle, float vitesse, float dt){
    x=x + vitesse*cos(angle)*dt;
    y=y + vitesse*sin(angle)*dt;
}

void calculCoordonnee_precise(float & x, float & y, float angle, float vitesse, float acc, float dt){
    x=x + cos(angle) * dt * (vitesse + 0.5*acc*dt);
    y=y + sin(angle) * dt * (vitesse + 0.5*acc*dt);
}

void rotation_xy(float & x, float & y, float angle){
    float x2 = x*cos(angle) - y*sin(angle);
    y = x*sin(angle) + y*cos(angle);
    x = x2;
}