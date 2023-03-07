#ifndef _COLLISION_H_
#define _COLLISION_H_

#include "Terrain.h"
#include "Voiture.h"

using namespace std;

bool testCol(Props & prop, Voiture & voiture);

bool testCol(Voiture & v1, Voiture & v2);


#endif