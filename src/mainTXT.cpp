#include <iostream>
#include <fstream>
#include <chrono>
#include <thread>

#include "Voiture/Physique.h"
#include "Voiture/Voiture.h"
#include "Voiture/Moteur.h"
#include "Voiture/Roues.h"
#include "Voiture/Vecteur.h"

#include "Terrain.h"
#include "Jeu.h"
#include "Collision.h"
#include "AffichageTXT.h"
#include "Editeur.h"
#include "Menu.h"

#include "External/json.hpp"
#include "External/winTxt.h"

using namespace std::this_thread; // sleep_for, sleep_until
using namespace std::chrono; // milliseconds, system_clock, seconds
using json = nlohmann::json; //pour le json
using namespace std;

int main(){

  Jeu J1;
  J1.ChargerTerrain("data/circuits/test.json");

  cout<<"voiture du jeu : ";
  afficherVoitureTxt(J1.getVoiture(0));
  cout<<"Terrain du jeu :"<<endl;
  afficherTerrainTxt(J1.getTerrain());
  cout << "init ok" << endl;
  sleep_for(milliseconds(2000));
  bool fin = false;
  float i = 0;
  J1.setframe_time(0.016);
  //sleep_for(milliseconds(2000));
  termClear();
  WinTXT win(J1.getTerrain().getLongueur()+20,J1.getTerrain().getLargeur()+20);
  bool pause = false;
  while (!fin){
    
    time_point<system_clock> start, end;
    start = system_clock::now();


    char a = win.getCh();
    if (a == 'p')
    { cout<<"pause"<<endl;
      pause = !pause;
      if (!pause) a = win.getCh();
    } 
    if (a == 'q') fin = true;

    if (!pause)
    { i+=0.008;
      J1.update(a);
      
      afficherJeuFTXT(win, J1, i, 5);
      
      end = system_clock::now();
      duration<double> elapsed_seconds = end-start;
      sleep_for(milliseconds(8) - duration_cast<milliseconds>(elapsed_seconds));
    }
  }
  termClear();
  cout << "Vous avez tapé un mur à " << J1.getVoiture(0).getVitesse()*3.6 << "km/h ! J'espère que vous aviez bien attaché la ceinture de sécurité !" << endl;
  
  return 0;
}