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
    Menu M1;
    GestionSFML G1;
    Editeur E1;
    E1.charger("data/circuits/test.json");
    bool quitter = false;
    // RenderWindow window(VideoMode(1280,720),"Vroum",Style::Fullscreen);
    while (!quitter){
        RenderWindow window(VideoMode(1280, 720), "Vroum", Style::Fullscreen);
        switch (M1.boucleMenu(window)){
            case 1:
                G1.boucleJeuSFML(window);
                break;

            case 2:
                E1.boucleEditeur(window);
                break;

            case 3:
                quitter = true;
                break;

            case 4:
                M1.boucleMenu(window);

            default:
                break;
        };
        if (quitter){
            window.close();
        }
    }
    return 0;
}