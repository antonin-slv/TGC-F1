#include "Voiture.h"
#include <iostream>
#include "Physique.h"
using namespace std;

int main(){
  //puissance en cheveaux : 1000
  Moteur M1 (string("Moteur 1"),1000*2.7*4);
  Roues R1 (string("Roues 1"),0,1);
  Voiture V1 (M1,R1,796,0.14,0,0);

  cout << "init ok" << endl;

  cout << "L'accélération de la voiture sera "
       << calculAcceleration(V1.getVitesse(),V1.getPoids(),V1.getCoefAero(),V1.getMoteur()->getPuissance())
       << " mètres par seconde carre " << endl;

  for (int i=0; i<1000; i++){
     
    if ((i<=100 or i>=901)and i%10==0){
      cout << "après " << (i+1)/10 << " secondes"<<endl;
     
      cout << "  vitesse : "<< V1.getVitesse()*3.6 << " km/h"  << endl;
      
      cout << "  position : "<<"("<< V1.getX()<<","<<V1.getY()<<")"<< endl;
    }
    V1.accelerer_sur(0.1);
    V1.calculPosition(0.1);
  }
  return 0;
}