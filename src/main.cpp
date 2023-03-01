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
       << calculAcceleration(V1.getVitesse(),V1.getAngle(),V1.getPoids(),V1.getCoefAero(),V1.getMoteur()->getPuissance()) << endl;

  return 0;
}