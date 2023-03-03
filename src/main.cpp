#include "Voiture.h"
#include <iostream>
#include "Physique.h"
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
  Voiture V2 (M1,R1,796,0.14,0,0);
  cout << "init ok" << endl;

  cout << "L'accélération de la voiture sera "
       << calculAcceleration(V1.getVitesse(),V1.getPoids(),V1.getCoefAero(),V1.getMoteur()->getPuissance())
       << " mètres par seconde carre " << endl;
  int j;
  for (int i=0; i<100; i++){
    if (i<=10 || i>=98)
    {
        cout << "après " << i << " secondes"<<endl;
      
        cout << "  1 vitesse : "<< V1.getVitesse()*3.6 << " km/h ";
        
        cout << ",  position : "<<"("<< V1.getX()<<","<<V1.getY()<<") , angle : "<<V1.getAngle()*180/M_PI<<"°"<<endl;

        cout << "  2 vitesse : "<< V2.getVitesse()*3.6 << " km/h ";
        
        cout << ", position : "<<"("<< V2.getX()<<","<<V2.getY()<<"), angle : "<<V2.getAngle()*180/M_PI<<"°"<<endl;
    }
    for (j=0;j<10;j++)
    {
      V1.calculAcc(0.1);
      V1.calculVitesse(0.1);
      V1.calculPosition(0.1);
    }

    V2.calculAcc(1);
    V2.calculPosition_precis(1);
    V2.calculVitesse(1);
    V2.tourner(M_PI/180/10,1);
    
    sleep_for(std::chrono::nanoseconds( 100000000));
    //sleep_until(system_clock::now() + seconds(1));}
    //system("cls");
    
  }
  return 0;
}