#include "Jeu.h"

Jeu::Jeu()
{   
    terrain = new Terrain(1000, 1000, 100);
    nb_voit = 1;
    tab_voit = new Voiture[nb_voit];
}

Jeu::~Jeu()
{
    if(terrain != nullptr) delete terrain;
    if(tab_voit != nullptr) delete [] tab_voit;
}