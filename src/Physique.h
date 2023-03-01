#include <math.h>

float calculAcceleration(float vitesse, float poids, float coef_aero, float puissance);

float calculVitesse(float vitesse, float acceleration, float dt);

void calculCoordonnee(float & x, float & y, float angle, float vitesse, float dt);