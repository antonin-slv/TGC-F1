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
#include "Interface.h"
#include <vector>
#include <iostream>

using namespace std;
using namespace sf;

class GestionSFML : public Jeu
{   private :
        float zoom;

        Sprite fond;
        Texture text_fond;
        Interface interface;
        
        
    public :
        GestionSFML();
        GestionSFML(int width, int height, std::string title);

        ~GestionSFML();

        void afficherterrain(Terrain & terrain, Vecteur centre, int rotation=0, int zoom=1);
        void afficherDebug(RenderWindow &Window, Text & texte1, Text & texte2);
        void afficherJeuSFML(sf::RenderWindow & window);
        void boucleJeuSFML(sf::RenderWindow & window);

        bool test_regression();

};

void getActionClavier(Event event, ActionClavier & action, Clock & _temps_au_tour);

#endif