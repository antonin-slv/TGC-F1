#ifndef PHYSIQUE_H
#define PHYSIQUE_H

#include <math.h>


float calculAcceleration(float vitesse, float poids, float coef_aero, float puissance);

float calculVitesse_P(float vitesse, float acceleration, float dt);

void calculCoordonnee(float & x, float & y, float angle, float vitesse, float dt);

void calculCoordonnee_precise(float & x, float & y, float angle, float vitesse, float acc, float dt);

void rotation_xy(float & x, float & y, float angle);

#endif