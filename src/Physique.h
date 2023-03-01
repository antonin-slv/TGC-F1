#include <math.h>

float calculAcceleration(float vitesse, float angle, float poids, float coef_aero, float puissance);

float calculVitesse(float vitesse, float angle, float poids, float coef_aero, float puissance, float dt);

void calculCoordonnee(float & x, float & y, float angle, float vitesse, float dt);