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
using json = nlohmann::json; // pour le json

/**
 * @brief Classe du jeu
 * 
 */
class Jeu
{   protected :
        Terrain terrain;
        vector<Voiture> tab_voit;
        float frame_time;
        int nb_voit;

        unsigned int nb_tour_max=1;
        unsigned int nb_tour;
        int num_checkpoint=-1;

    public:
         /** \brief Constructeur par défaut \return Jeu */
        Jeu();
         /** \brief Constructeur avec paramètres \param path lien du fichier à charger \return Jeu */
        Jeu(string path);
         /** \brief Destructeur */
        ~Jeu();
        
         /** \brief Debug pour tenter de charger un terrain \return Terrain */
        Terrain &  getTerrain();
         /** \brief Debug pour tenter de charger une voiture (non fait) \return Voiture */
        Voiture & getVoiture(int i=0);
        
        void restart();

         /** \brief Définit le temps d'une frame \param tps Temps d'une frame */
        void setframe_time(float const & tps);
         /** \brief Charge un terrain, pose la voiture au bon endroit.
          *  \param path chemin vers le fichier */
        void ChargerTerrain(string path, int nb_tours=3);
         /** \brief Ajoute une voiture \param V Voiture à ajouter, passé par référence */
        void ajouterVoiture(Voiture const & V);
        

        //retirer le bool a terme ?
         /** \brief Met à jour le jeu \param action actions du joueur \return void */
        
        int update(ActionClavier const & action);

        int getNbTours() const { return (int)nb_tour; }

        
};



#endif