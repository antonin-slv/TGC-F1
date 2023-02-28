#include "Roues.h"
#include <iostream>
using namespace std;

Roues::Roues(char n[16],float o, float g){
    nom = n;
    orientation = o;
    grip = g;
    cout << "Construct roues";
}