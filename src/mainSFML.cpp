#include <iostream>
#include <fstream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>

#include "Voiture/Voiture.h"
#include "Voiture/Vecteur.h"

#include "Terrain.h"
#include "Jeu.h"
#include "Collision.h"
#include "GestionaireSFML.h"
#include "Editeur.h"
#include "Menu.h"

#include "External/json.hpp"

using namespace sf;
using json = nlohmann::json; // pour le json
using namespace std;

int main(){

    int volume = 50;
    float decalage = 0;
    
    GestionSFML G1;
    Editeur E1;

    Clock temps_au_tour;

    E1.charger("data/circuits/test.json");
    bool quitter = false;
    RenderWindow window(VideoMode(1920, 1080), "TGC : F1", Style::Fullscreen);
    window.setFramerateLimit(120);
    while (!quitter){
        string action = boucleMenu(window, volume, decalage);
        if (action == "niveau_1"){
            G1.boucleJeuSFML(window, temps_au_tour, decalage);
        }
        else if (action == "niveau_2"){
            G1.boucleJeuSFML(window, temps_au_tour, decalage);
        }
        else if (action == "niveau_3"){
            G1.boucleJeuSFML(window, temps_au_tour, decalage);
        }
        else if (action == "niveau_4"){
            G1.boucleJeuSFML(window, temps_au_tour, decalage);
        }
        else if (action == "niveau_5"){
            G1.boucleJeuSFML(window, temps_au_tour, decalage);
        }
        else if (action == "editeur"){
            E1.boucleEditeur(window, volume);
        }
        else if (action == "quitter"){
            quitter = true;
            window.close();
        }
    }
    return 0;
}