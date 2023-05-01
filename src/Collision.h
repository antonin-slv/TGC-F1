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
 * point est dans les coordonnées locales de la box
 * 
 * @param x position x du point
 * @param y position y du point
 * @param l longueur du rectangle
 * @param L Largeur du rectangle
 * @return true si le point est dans le rectangle, false sinon
 */
bool test_point_in_box(float x, float y, float l, float L);

/**
 * @brief Teste si un point est dans un rectangle via les vecteurs
 * 
 * @param point point à tester dans les cooronées de la box
 * @param box rectangle à tester (box.x : longueur, box.y : largeur)
 * @return bool
 */
bool test_point_in_box(Vecteur point, Vecteur box);

/**
 * @brief Teste si un point est dans la box, avec prise en compte de la rotation de la box
 * 
 * box est centrée en 0,0.
 * 
 * @param point point à tester
 * @param box boite de collision (centrée en 0,0)
 * @param Rotation rotation de la box
 * @return true si le point est dans la box, false sinon
 */
bool test_colPointbox(Vecteur point, Vecteur const &  box, float Rotation);

/**
 * @brief Teste si la voiture est en collision avec le prop
 * 
 * @param voit voiture à tester
 * @param prop prop à tester
 * @return true si la voiture est en collision avec le prop, false sinon
 */
bool testColPropVoit(Props const & prop, Voiture & voit);

/**
 * @brief Applique les effets de collision entre la voiture et le prop (cas d'un prop de collision)
 * 
 * @param prop le prop dont on sait qu'il a été touché
 * @param voit la voiture qui a touché le prop
 */
void collisionPropVoit(Props const & prop, Voiture & voit);


#endif