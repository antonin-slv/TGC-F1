#include <iostream>
#include <fstream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>

#include "GestionaireSFML.h"
#include "Editeur.h"
#include "Menu.h"

#include "External/json.hpp"

using namespace sf;
using json = nlohmann::json; // pour le json
using namespace std;

int main() {
    Selection action;
    action.volume = 50;
    action.decalage = 0;
    action.choix = "menu";
    action.nb_tours = 3;
    
    GestionSFML G1;
    Editeur E1;

    Clock temps_au_tour;
    bool quitter = false;
    RenderWindow window(VideoMode(1920, 1080), "TGC : F1", Style::Fullscreen);
    window.setFramerateLimit(120);
    Time temps;
    
    while (!quitter){

        boucleMenu(window, action);
        if (action.choix == "Jouer"){
            G1.chargerNiveau(action.chemin_circuit,action.nb_tours);
            temps_au_tour.restart();
            temps=G1.boucleJeuSFML(window, temps_au_tour, action.decalage);
            window.setVisible(false);
            //on enregistre le temps dans la liste des temps du circuit
            if ( sauvegarderTemp(action, temps.asSeconds())) cout<<"Temps enregistré"<<endl;
            else cout<<"Temps non enregistré"<<endl;
            window.setVisible(true);
        }
        else if (action.choix == "editeur"){
            E1.charger(action.chemin_circuit);
            E1.boucleEditeur(window, action.volume);
        }
        else if (action.choix == "quitter"){
            quitter = true;
            window.close();
        }
    }
    return 0;
}

/* 
void (*pointeur_fct)(int) = &fonction;
ou
void (*pointeur_fct)(int) = fonction;

--> génère un pointeur sur la fonction fonction(int)
alors, pointeur_fct peut s'utiliser exactement comme fonction(int)
*/