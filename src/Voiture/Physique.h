#ifndef PHYSIQUE_H
#define PHYSIQUE_H

#include <math.h>

/**
 * @brief Calcul de l'accélération
 * \param vitesse Vitesse de la voiture
 * \param poids Poids de la voiture
 * \param coef_aero Coefficient aérodynamique de la voiture
 * \param puissance Puissance du moteur
 * \return float
 */
float calculAcceleration(float vitesse, float poids, float coef_aero, float puissance);

/**
 * @brief Calcul de la vitesse
 * \param vitesse Vitesse de la voiture
 * \param acceleration Accélération de la voiture
 * \param dt Delta temps
 * \return float
 */
float calculVitesse_P(float vitesse, float acceleration, float dt);

/**
 * @brief Calcul des coordonnées
 * 
 * @param x passé par référence
 * @param y passé par référence
 * @param angle 
 * @param vitesse 
 * @param dt
 */
void calculCoordonnee(float & x, float & y, float angle, float vitesse, float dt);

/**
 * @brief Calcul des coordonnées (plus précis)
 * 
 * @param x passé par référence
 * @param y passé par référence
 * @param angle 
 * @param vitesse 
 * @param acc 
 * @param dt
 */
void calculCoordonnee_precise(float & x, float & y, float angle, float vitesse, float acc, float dt);

/**
 * @brief Rotation des coordonnées x et y passées par référence, dans le sens trigonométrique
 * 
 * @param x passé par référence
 * @param y passé par référence
 * 
 * @param angle 
 */
void rotation_xy(float & x, float & y, float angle);

#endif