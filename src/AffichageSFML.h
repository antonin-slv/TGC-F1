#ifndef _AFFICHAGESFML_H_
#define _AFFICHAGESFML_H_

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include "Editeur.h"
#include "Jeu.h"
#include "Menu.h"
#include "Terrain.h"
#include "Voiture/Voiture.h"
#include "Voiture/Vecteur.h"
#include <iostream>

//pas fait
/** \brief Affiche le terrain en mode graphique (non fait) */
void afficher(Terrain & terrain, int x, int y, int rotation, int zoom);

 /** \brief Affiche le jeu en mode graphique SFML (non fait) */
void afficherJeuSFML(Jeu & jeu);

 /** \brief Affiche l'éditeur en mode graphique (non fait) */
void afficher(Editeur & editeur);

#endif