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
using namespace std::chrono; // milliseconds, system_clock, seconds
using json = nlohmann::json; //pour le json
using namespace std;

int main(){
  /*
  Jeu J1;
  J1.ChargerTerrain("data/circuits/test.json");
  J1.setframe_time(0.016);
  float zoom = 10;

  // Création de la fenêtre et des objets
  RenderWindow window(VideoMode(1280,720),"Vroum",Style::Fullscreen);
  RectangleShape V1(Vector2f(J1.getVoiture(0).getLongueur()*zoom,J1.getVoiture(0).getLargeur()*zoom));
  V1.setFillColor(Color(255,0,0));
  V1.setPosition(J1.getVoiture(0).getX()*zoom,J1.getVoiture(0).getY()*zoom);

  Font font;
  if (!font.loadFromFile("arial.ttf")){
    cout << "Souci de police" << endl;
  }

  Text text;
  // choix de la police à utiliser
  text.setFont(font); // font est un sf::Font
  // choix de la chaîne de caractères à afficher
  text.setString("Hello world");
  // choix de la taille des caractères
  text.setCharacterSize(24); // exprimée en pixels, pas en points !
  // choix de la couleur du texte
  text.setFillColor(sf::Color::Red);
  // choix du style du texte
  text.setStyle(sf::Text::Bold | sf::Text::Underlined);

  // Boucle du programme
  while (window.isOpen()){
    // On traite tous les évènements de la fenêtre qui ont été générés depuis la dernière itération de la boucle
    Event event;
    while (window.pollEvent(event)){
      // Partie physique
      if(Keyboard::isKeyPressed(Keyboard::O)){
        J1.update('o');
      }
        
      else if(Keyboard::isKeyPressed(Keyboard::K)){
        J1.update('k');
      }

      else if(Keyboard::isKeyPressed(Keyboard::L)){
        J1.update('l');
      }

      else if(Keyboard::isKeyPressed(Keyboard::M)){
        J1.update('m');
      }
      else J1.update(' ');

      V1.setPosition(J1.getVoiture(0).getX()*zoom,J1.getVoiture(0).getY()*zoom);
      //V1.setPosition(50,50);
      V1.setRotation(J1.getVoiture(0).getAngle());
      
    
      // Fermeture de la fenêtre avec la croix (inutile pour le moment)
      if (event.type == Event::Closed){
        window.close();
      }

      // Clear en noir
      window.clear(Color::Black);

      // Dessins
      window.draw(V1);
      window.draw(text);

      if(Keyboard::isKeyPressed(Keyboard::Q)){
        window.close();
      }

      // Affichage
      window.display();
    }
  }
  */
  Editeur E1;
  E1.test_regression();

  GestionSFML G1;
  G1.initWindow(1280,720,"Vroum");
  G1.boucleJeuSFML();
  return 0;
}