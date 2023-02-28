 #include "Voiture.h"
 #include <iostream>
 using namespace std;

 int main(){
   
   Moteur M1 (string("Moteur 1"),100);
   Roues R1 (string("Roues 1"),0,1);
   Voiture V1 (M1,R1,0,0,1000,1);
   cout << "All ok !" << endl;

   return 0;
 }