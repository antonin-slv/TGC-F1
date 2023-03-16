#include <iostream>
#include <fstream>
#include <chrono>
#include <thread>
#include "Voiture/Physique.h"
#include "Voiture/Voiture.h"
#include "Terrain.h"
#include "Jeu.h"
#include "Affichage.h"
#include "Collision.h"

#include "json.hpp"

using namespace std::this_thread; // sleep_for, sleep_until
using namespace std::chrono; // milliseconds, system_clock, seconds
using json = nlohmann::json; //pour le json
using namespace std;

int main(){
  Voiture V1;

  Jeu J1;
  J1.ChargerTerrain("data/circuits/test.json");
  J1.getVoiture(0).accelerer(100);
  cout<<"voiture du jeu : ";
  afficherVoitureTxt(J1.getVoiture(0));
  cout<<"Terrain du jeu :"<<endl;
  afficherTerrainTxt(J1.getTerrain());

  cout << "init ok" << endl;

  cout << "L'accélération de la voiture sera "
       << calculAcceleration(V1.getVitesse(),V1.getPoids(),V1.getCoefAero(),V1.getMoteur()->getPuissance())
       << " mètres par seconde carre " << endl;
  
  bool fin = false;
  bool i = 0;

  while (!fin){
    time_point<system_clock> start, end;
    start = system_clock::now();
    i+=1/60;
    V1.accelerer(1/60);
    cout << i << "ms" << endl;
    afficherVoitureTxt(V1);
    end = system_clock::now();
    duration<double> elapsed_seconds = end-start;
    sleep_for(milliseconds(8) - duration_cast<milliseconds>(elapsed_seconds));
    
    fin = testColPropVoit(J1.getTerrain().getProp(1),V1);
  }
  cout << "Vous aveez tapé un mur à " << V1.getVitesse()*3.6 << "km/h ! J'espère que vous aviez bien attaché la ceinture de sécurité !" << endl;
  
  return 0;
}