#ifndef _JEU_H_
#define _JEU_H_


#include "Terrain.h"
#include "Voiture/Voiture.h"
#include "Voiture/Physique.h"
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


        void ChargerTerrain(string const & nom_fichier);
        void AjouterVoiture(Voiture const & V);
        
        void update(char const & touche);




};



#endif