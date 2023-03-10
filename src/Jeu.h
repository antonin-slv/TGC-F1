#ifndef _JEU_H_
#define _JEU_H_


#include "Terrain.h"
#include "Voiture/Voiture.h"
#include "Voiture/Physique.h"
#include <iostream>
#include <vector>

using namespace std;

class Jeu
{   
    public:
        Jeu();
        ~Jeu();

        //fonctions de debug
        Terrain *  getTerrain() const ;
        Voiture & getVoiture(int i=0);
        void ChargerTerrain(string const & nom_fichier);
        void AjouterVoiture(Voiture & V);
        
    private:

        Terrain * terrain;
        vector<Voiture> tab_voit;
        int nb_voit;

};



#endif