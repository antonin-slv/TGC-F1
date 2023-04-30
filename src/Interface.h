#ifndef _INTERFACE_
#define _INTERFACE_

#include "Jeu.h"
#include "Terrain.h"
#include "Voiture/Voiture.h"

struct Editeur;


#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include <vector>
#include <iostream>

using namespace std;
using namespace sf;

void afficherDebug(RenderWindow & window, Text & text, int charac_size, float _x, float _y);

class Interface
{   private :
    vector<Sprite> props;//charger depuis un terrain
    vector<Sprite> ref_props;//chargés quand on ouvre un editeur
    
    Texture checkpoint;
    Texture finish;
    Texture grass;
    Texture road_kerb_a;
    Texture road_kerb_m;
    Texture road_kerb_z;

    Texture road;
    Texture turn1;
    Texture turn2;
    Texture turn3;
    Texture turn4;

    Texture text_voiture;//temporaire en attente de multiple voitures
    Texture text_voiture_ombre;//pour l'ombre de la voiture
    Sprite voiture_ombre;
    public :

    View vue;

    Sprite voiture;
    Interface();

    void supprimerProp(int i=-1);
    void clearProps();
    void clearVoitures();

    void loadProp(Props const & prop);
    void loadTerrain(Terrain & terrain,string texture_path);
    void loadVoiture(Voiture & voiture_, string texture_path);
    void loadRefProps();

    void drawTerrain(RenderWindow & window);
    void drawVoiture(RenderWindow & window,Voiture & voiture_);
    void drawVoitureHitbox(RenderWindow & window,Voiture & voiture_);
    void drawJeu(Jeu const & jeu,RenderWindow & window);
    void drawEditeur(RenderWindow & window);

    Texture * getTexture(Tip t);
    void drawRefProps(RenderWindow & window);

    Tip refPropSelected(RenderWindow const & window);

    Sprite & dernierProp();
    Sprite & getProp(int i);
};

#endif