#include <iostream>
#include <fstream>
#include <chrono>
#include <thread>
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
using json = nlohmann::json; //pour le json
using namespace std;

int main(){
  GestionSFML G1;
  Editeur E1;
  bool quitter = false;
  string choix="1";
  //RenderWindow window(VideoMode(1280,720),"Vroum",Style::Fullscreen);
  do{
    RenderWindow window(VideoMode(1280,720),"Vroum",Style::Fullscreen);
    if (choix == "2") E1.boucleEditeur(window);
    else if (choix == "1") G1.boucleJeuSFML(window);
    else quitter = true;
    window.close();
    if (!quitter) {  
      cout<<"entrer 1 pour jouer, 2 pour editer, 3 pour quitter :"<<endl;
      cin>>choix;
  
    }

  }while(!quitter);
  return 0;
}