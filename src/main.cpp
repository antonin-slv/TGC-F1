#include "Voiture.h"
#include <iostream>
using namespace std;

int main(){
  Moteur M1 (string("Moteur 1"),1000);
  Roues R1 (string("Roues 1"),0,1);
  Voiture V1 (M1,R1,0,0,796,0.14);
  cout << "All ok !" << endl;

  cout << "L'accélération de la voiture sera " << V1.claculAcceleration() << endl;

  return 0;
}