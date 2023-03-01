#include "Voiture.h"
#include <iostream>
#include "Physique.h"
using namespace std;

int main(){
  //puissance en cheveaux : 1000
  Moteur M1 (string("Moteur 1"),1000);
  Roues R1 (string("Roues 1"),0,1);
  Voiture V1 (M1,R1,796,0.14,0,0);

  cout << "init ok" << endl;

  cout << "L'accélération de la voiture sera "
       << calculAcceleration(V1.getVitesse(),V1.getPoids(),V1.getCoefAero(),V1.getMoteur()->getPuissance())
       << " mètres par seconde carre " << endl;

  for (int i=0; i<10; i++){
    cout << "après " << i+1 << " secondes"<<endl;
    V1.accelerer_sur(1);
    cout << "  vitesse : "<< V1.getVitesse() << endl;
    V1.calculPosition(1);
    cout << "  position : "<<"("<< V1.getX()<<","<<V1.getY()<<")"<< endl;
  }
  return 0;
}