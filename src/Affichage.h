#ifndef _AFFICHAGE_H_
#define _AFFICHAGE_H_

#include "Editeur.h"
#include "Jeu.h"
#include "Menu.h"
#include "Terrain.h"
#include "Voiture/Voiture.h"
#include "winTxt.h"


//plus ou moins ok -> j'ai pas compris pourquoi on peut pas mettre de const devant terrain...
void afficherPropsTxt(Props const & p);
void afficherTerrainGenTxt(Terrain * terrain);
void afficherTerrainTxt(Terrain * terrain);
void afficherTerrainTxt(Terrain & terrain);
void afficherVoitureTxt(Voiture & voit);

//AFFICHE LE JEU EN TXT Fenetré

void afficherJeuFTXT(Jeu & jeu);


//pas fait
void afficher(Terrain & terrain, int x, int y, int rotation, int zoom);

void afficherJeuTXT(Jeu & jeu);
void afficherJeuSFML(Jeu & jeu);


void afficher(Editeur & editeur);


#endif