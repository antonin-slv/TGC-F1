#include "Voiture.h"
#include <iostream>
#include "Physique.h"
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
      
        cout << " 1 vitesse : "<< V1.getVitesse()*3.6 << " km/h"  << endl;
        
        cout << " 1 position : "<<"("<< V1.getX()<<","<<V1.getY()<<")"<< endl;

        cout << " 2 vitesse : "<< V2.getVitesse()*3.6 << " km/h"  << endl;
        
        cout << " 2 position : "<<"("<< V2.getX()<<","<<V2.getY()<<")"<< endl;
    }
    for (j=0;j<100;j++)
    {
      V1.accelerer_sur(0.01);
      V1.calculPosition(0.01);
    }
    V2.calculPosition_precis(1);
  }
  return 0;
}