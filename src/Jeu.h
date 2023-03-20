#ifndef _JEU_H_
#define _JEU_H_


#include "Terrain.h"
#include "Voiture/Voiture.h"
#include "Voiture/Physique.h"
#include "Collision.h"
#include "External/json.hpp"

#include <iostream>
#include <vector>

using namespace std;

class Jeu
{   private :
        Terrain terrain;
        vector<Voiture> tab_voit;
        float frame_time;
        int nb_voit;

    public:
        Jeu();
        Jeu(string const & nom_fichier);
        ~Jeu();

        //ajouter chargement voiture

        //fonctions de debug
        Terrain &  getTerrain() ;
        Voiture & getVoiture(int i=0);
        


        void setframe_time(float const & tps);

        void ChargerTerrain(string const & nom_fichier);
        void AjouterVoiture(Voiture const & V);
        

        //retirer le bool a terme ?
        int update(char const & touche);
    
};



#endif