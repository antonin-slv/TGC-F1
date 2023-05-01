#ifndef _AFFICHAGE_TXT_H_
#define _AFFICHAGE_TXT_H_

#include "Editeur.h"
#include "Jeu.h"
#include "Menu.h"
#include "Terrain.h"
#include "Voiture/Voiture.h"
#include "External/winTxt.h"
#include "Voiture/Vecteur.h"
#include <iostream>

/** \brief Module permettant d'afficher le jeu en mode texte (ne fonctionne plus)
 *  
*/

/** \brief Affiche les propriétés d'un props */
void afficherPropsTxt(Props const & p);
/** \brief Affiche les propriétés d'un terrain */
void afficherTerrainGenTxt(Terrain * terrain);
/** \brief Affiche les propriétés d'un terrain et celles de chacun de ses props */
void afficherTerrainTxt(Terrain & terrain);
/** \brief Affiche les propriétés d'une voiture */
void afficherVoitureTxt(Voiture & voit);

//AFFICHE LE JEU EN TXT Fenetré

/** \brief Affiche le jeu en mode texte fenetré textuel
 * 
 * Ne fonctionne plus, était basé sur les hitbox des objets.
*/
void afficherJeuFTXT(WinTXT & win,Jeu & jeu, const int i, const int zoom=10);




#endif