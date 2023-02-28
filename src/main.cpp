 #include "Voiture.h"
 #include <iostream>
 using namespace std;

 int main(){
    M1 = Moteur("Moteur 1",100);
    R1 = Roues("Roues 1",0,1);
    V1 = Voiture(M1,R1,0,0,1000,1);

    return 0;
 }