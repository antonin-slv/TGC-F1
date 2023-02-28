#ifndef ROUES_H
#define ROUES_H

#include <iostream>
#include <string>

using namespace std;

class Roues{
    private:
        string nom;
        float orientation, grip;
    public:
        Roues();
        Roues(string n,float o, float g);
        Roues(const Roues & R);
};

#endif