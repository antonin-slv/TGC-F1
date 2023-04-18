#ifndef _COLLISION_H_
#define _COLLISION_H_

#include "Terrain.h"
#include "Voiture/Voiture.h"
#include "Voiture/Vecteur.h"
#include <iostream>
using namespace std;

/**
 * @brief Teste si un point est dans un rectangle
 * 
 * @param x 
 * @param y 
 * @param l 
 * @param L
 * @return bool
 */
bool test_point_in_box(float x, float y, float l, float L);

/**
 * @brief Teste si un point est dans un rectangle via les vecteurs
 * 
 * @param point 
 * @param box 
 * @return bool
 */
bool test_point_in_box(Vecteur point, Vecteur box);

/**
 * @brief Teste si un point est dans un rectangle via les vecteurs
 * 
 * @param point 
 * @param box 
 * @param Rotation 
 * @return bool
 */
bool test_colPointbox(Vecteur point, Vecteur const &  box, float Rotation);

/**
 * @brief Teste si 8 points sont dans un rectangle (ancienne méthode)
 * 
 * @param voit 
 * @param position 
 * @param box 
 * @param Rotation 
 * @return bool
 */
bool testColPropVoit2(Props const & prop, Voiture & voit);

/**
 * @brief Teste si 8 points sont dans un rectangle (avec les vecteurs)
 * 
 * @param voit 
 * @param position 
 * @param box 
 * @param Rotation 
 * @return bool
 */
bool testColPropVoit(Props const & prop, Voiture & voit);

/**
 * @brief Applique les effets de collision entre la voiture et le prop
 * 
 * @param prop 
 * @param voit 
 */
void collisionPropVoit(Props const & prop, Voiture & voit);


#endif