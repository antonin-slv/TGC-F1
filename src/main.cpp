#include <iostream>
#include <fstream>
#include "Voiture.h"
#include "Physique.h"
#include "Jeu.h"
/* librairies pour le chrono */

#include <chrono>
#include <thread>

using namespace std::this_thread; // sleep_for, sleep_until
using namespace std::chrono; // nanoseconds, system_clock, seconds



using namespace std;

int main(){
  //puissance en cheveaux : 1000
  Moteur M1 (string("Moteur 1"),1000*2.7*3.5);
  Roues R1 (string("Roues 1"),0,1);
  Voiture V1 (M1,R1,796,0.14,0,0);
  Voiture V2 (V1);
  cout << "init ok" << endl;

  cout << "L'accélération de la voiture sera "
       << calculAcceleration(V1.getVitesse(),V1.getPoids(),V1.getCoefAero(),V1.getMoteur()->getPuissance())
       << " mètres par seconde carre " << endl;
  for (int i=0; i<110; i++){
      if (i<=10 || i>=90){
          cout << "après " << i << " secondes"<<endl;
        
          cout << "  1 vitesse : "<< V1.getVitesse()*3.6 << " km/h ";
          
          cout << ",  position : "<<"("<< V1.getX()<<","<<V1.getY()<<") , angle : "<<V1.getAngle()*180/M_PI<<"°"<<endl;

          cout << "  2 vitesse : "<< V2.getVitesse()*3.6 << " km/h ";
          
          cout << ", position : "<<"("<< V2.getX()<<","<<V2.getY()<<"), angle : "<<V2.getAngle()*180/M_PI<<"°"<<endl;
      }
    V1.accelerer(1);
    if (i>=90 and i< 95) V2.ralentir(1);//acceleration max pendant 1 sec
    else if (i >= 90) for (int j=0;j<10;j++) V2.freiner(0.1);//freinage max pendant 1 sec
    else V2.accelerer(1);//acceleration max pendant 1 sec
    //  V2.tourner_d(1);//rotaion max à droite pendant 1 sec
      
      //sleep_for(std::chrono::nanoseconds( 100000000));
      //sleep_until(system_clock::now() + seconds(1));}
      //system("cls");
    
  }

  Terrain T1;
  T1.chargerJSON("../data/circuits/test.json");

  return 0;
}