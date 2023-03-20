#ifndef _AFFICHAGE_H_
#define _AFFICHAGE_H_

#include "Editeur.h"
#include "Jeu.h"
#include "Menu.h"
#include "Terrain.h"
#include "Voiture/Voiture.h"
#include "External/winTxt.h"


//plus ou moins ok -> j'ai pas compris pourquoi on peut pas mettre de const devant terrain...
void afficherPropsTxt(Props const & p); /** \brief Affiche les propriétés d'un props */
void afficherTerrainGenTxt(Terrain * terrain); /** \brief Affiche les propriétés d'un terrain */
void afficherTerrainTxt(Terrain * terrain); /** \brief Affiche les propriétés d'un terrain et de ses props */
void afficherTerrainTxt(Terrain & terrain); /** \brief Affiche les propriétés d'un terrain et de ses props */
void afficherVoitureTxt(Voiture & voit); /** \brief Affiche les propriétés d'une voiture */

//AFFICHE LE JEU EN TXT Fenetré

void afficherJeuFTXT(Jeu & jeu); /** \brief Affiche le jeu en mode texte fenetré (non fait) */


//pas fait
void afficher(Terrain & terrain, int x, int y, int rotation, int zoom); /** \brief Affiche le terrain en mode graphique (non fait) */

void afficherJeuTXT(Jeu & jeu); /** \brief Affiche le jeu en mode texte (non fait) */
void afficherJeuSFML(Jeu & jeu); /** \brief Affiche le jeu en mode graphique SFML (non fait) */


void afficher(Editeur & editeur); /** \brief Affiche l'éditeur en mode texte (non fait) */


#endif