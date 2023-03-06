#ifndef _JEU_H_
#define _JEU_H_


#include "Terrain.h"
#include "Voiture.h"
#include "Physique.h"
#include <iostream>

using namespace std;

class Jeu
{   
    public:
        Jeu();
        ~Jeu();
        void run();
    
    private:
        Terrain * terrain;
        Voiture * tab_voit;
        int nb_voit;

};



#endif