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
using json = nlohmann::json; //pour le json
using namespace std;

int main(){
  GestionSFML G1;
  G1.boucleJeuSFML();
  return 0;
}