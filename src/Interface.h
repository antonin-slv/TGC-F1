#ifndef _INTERFACE_
#define _INTERFACE_

#include "jeu.h"
#include "terrain.h"
#include "Voiture/voiture.h"
#include "editeur.h"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include <vector>
#include <iostream>

using namespace std;
using namespace sf;

class Interface
{ private :
    vector<RectangleShape> props;//charger depuis un terrain
    vector<Sprite> voitures;//charger depuis un jeu
    
    vector<Texture> text_props;
    
    Texture text_voiture;//temporaire en attente de multiple voitures
    public :
    Sprite voiture;
    Interface();


    void loadTerrain(Terrain & terrain,string texture_path);
    void loadVoiture(Voiture & voiture_, string texture_path);
    void loadJeu(Jeu & jeu, string texture_path);

    void drawTerrain(RenderWindow & window);
    void drawVoiture(RenderWindow & window,Voiture & voiture_);
    void drawJeu(Jeu const & jeu,RenderWindow & window);
    void drawEditeur(RenderWindow & window);
};

#endif