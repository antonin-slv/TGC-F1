#ifndef _AFFICHAGE_H_
#define _AFFICHAGE_H_

#include "Editeur.h"
#include "Jeu.h"
#include "Menu.h"
#include "Terrain.h"


void afficherPropsTxt(Props const * p);
void afficherTerrainGenTxt(Terrain & terrain);
void afficherTerrainTxt(Terrain & terrain);

void afficherVoitureTxt(Voiture & voit);


void afficher(Terrain & terrain, int x, int y, int rotation, int zoom);

void afficherJeuTXT(Jeu & jeu);
void afficherJeuSFML(Jeu & jeu);


void afficher(Editeur & editeur);


#endif