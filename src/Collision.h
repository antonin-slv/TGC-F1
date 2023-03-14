#ifndef _COLLISION_H_
#define _COLLISION_H_

#include "Terrain.h"
#include "Voiture/Voiture.h"

#include <iostream>
using namespace std;

//teste si un point est dans une rectangle centré ed largeur L et de longueur l
bool test_point_int_box(float x, float y, float l, float L);

//test si 8 points de la voiture sont dans le props

bool testColPropVoit(Props & prop, Voiture & voit);

//bool testColBlova(Props const & prop, Voiture const & voit);

bool testCol(Voiture & v1, Voiture & v2);


#endif