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

#include <vector>
#include <iostream>



class GestionSFML : public Jeu
{   private :
        float zoom;
        sf::RenderWindow window;
        vector<sf::RectangleShape> voitures;
        vector<sf::RectangleShape> obstacles;
        
        float rotation;
        
    public :
        GestionSFML();
        GestionSFML(int width, int height, std::string title);

        ~GestionSFML();

        void initWindow(int width, int height, std::string title);
        void afficherterrain(Terrain & terrain, Vecteur centre, int rotation=0, int zoom=1);
        void afficherJeuSFML(sf::RenderWindow & window);
        void boucleJeuSFML();

};


void initWindow(sf::RenderWindow & window, int width, int height, std::string title);

/** \brief Affiche le terrain en mode graphique (non fait) */
void afficherterrain(Terrain & terrain, Vecteur centre, int rotation=0, int zoom=1);

 /** \brief Affiche le jeu en mode graphique SFML (non fait) */
//void afficherJeuSFML(Jeu & jeu);

 /** \brief Affiche l'éditeur en mode graphique (non fait) */
void afficher(Editeur & editeur);

#endif