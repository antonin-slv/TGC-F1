#include "Roues.h"
#include <iostream>
using namespace std;

Roues::Roues(){
    nom = string("");
    orientation = 0;
    grip = 0;
    cout << "Construct roues vide" << endl;
}
Roues::Roues(string n,float o, float g){
    nom = n;
    orientation = o;
    grip = g;
    cout << "Construct roues" << endl;
}

Roues::Roues(const Roues & R){
    nom = R.nom;
    orientation = R.orientation;
    grip = R.grip;
    cout << "Construct roues copie" << endl;
}

string Roues::getNom(){
    return nom;
}

float Roues::getOrientation(){
    return orientation;
}

float Roues::getGrip(){
    return grip;
}