#include <iostream>
#include <fstream>
#include "Voiture.h"
#include "Physique.h"
#include "Jeu.h"
#include "Terrain.h"
#include "json.hpp"
/* librairies pour le chrono */

#include <chrono>
#include <thread>

using namespace std::this_thread; // sleep_for, sleep_until
using namespace std::chrono; // nanoseconds, system_clock, seconds
using json = nlohmann::json;
using namespace std;

int main(){
  Voiture V1;
  Voiture V2;

  Jeu J1;
  J1.ChargerTerrain("data/circuits/test.json");
  J1.getVoiture(0)->accelerer(100);
  cout<<"voiture du jeu : ";
  J1.getVoiture(0)->afficher_txt();
 // J1.terrain[1].

  cout << "init ok" << endl;

  cout << "L'accélération de la voiture sera "
       << calculAcceleration(V1.getVitesse(),V1.getPoids(),V1.getCoefAero(),V1.getMoteur()->getPuissance())
       << " mètres par seconde carre " << endl;
  for (int i=0; i<10; i++){
      if (i<=10 || i>=90){
          cout << "après " << i << " secondes"<<endl;
        
          cout << "  V 1 ";
          V1.afficher_txt();

          cout << "  V 2 ";
          V2.afficher_txt();
      }
    V1.accelerer(1);
    if (i>=90 and i< 95) V2.ralentir(1);//acceleration max pendant 1 sec
    else if (i >= 90) for (int j=0;j<10;j++) V2.freiner(0.1);//freinage max pendant 1 sec
    else V2.accelerer(1);//acceleration max pendant 1 sec
    V2.tourner_d(1);//rotaion max à droite pendant 1 sec
      
      //sleep_for(std::chrono::nanoseconds( 100000000));
      //sleep_until(system_clock::now() + seconds(1));}
      //system("cls");
    
  }

  return 0;
}