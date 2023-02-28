#include "Roues.h"
#include <iostream>
using namespace std;

Roues::Roues(){
    nom = string("");
    orientation = 0;
    grip = 0;
    cout << "Construct roues vide";
}
Roues::Roues(string n,float o, float g){
    nom = n;
    orientation = o;
    grip = g;
    cout << "Construct roues";
}

Roues::Roues(const Roues & R){
    nom = R.nom;
    orientation = R.orientation;
    grip = R.grip;
    cout << "Construct roues copie";
}