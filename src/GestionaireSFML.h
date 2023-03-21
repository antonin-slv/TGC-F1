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



class GestionSFML : public Jeu
{   private :
        float zoom;
        sf::RenderWindow window;
        sf::RectangleShape rectangle;
        Vecteur centre;
        float rotation;

    public :
        GestionSFML();
        GestionSFML(int width, int height, std::string title);
        void initWindow(int width, int height, std::string title);
        void afficherterrain(Terrain & terrain, Vecteur centre, int rotation=0, int zoom=1);
        void afficherJeuSFML();
        void boucleJeuSFML();

}


void initWindow(sf::RenderWindow & window, int width, int height, std::string title);

/** \brief Affiche le terrain en mode graphique (non fait) */
void afficherterrain(Terrain & terrain, Vecteur centre, int rotation=0, int zoom=1);

 /** \brief Affiche le jeu en mode graphique SFML (non fait) */
void afficherJeuSFML(Jeu & jeu);

 /** \brief Affiche l'éditeur en mode graphique (non fait) */
void afficher(Editeur & editeur);

#endif