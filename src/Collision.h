#ifndef _COLLISION_H_
#define _COLLISION_H_

#include "Terrain.h"
#include "Voiture/Voiture.h"
#include "Voiture/Vecteur.h"
#include <iostream>
using namespace std;

//teste si un point est dans une rectangle centré ed largeur L et de longueur l
bool test_point_in_box(float x, float y, float l, float L);
bool test_point_in_box(Vecteur point, Vecteur box);

//test si 8 points de la voiture sont dans le props
bool testColPropVoit2(Props & prop, Voiture & voit);//ancienne methide
bool testColPropVoit(Props & prop, Voiture & voit);//utilise vecteurs

//donne les effets de collision entre une voiture et un props
void collisionPropVoit(Props & prop, Voiture & voit);


#endif