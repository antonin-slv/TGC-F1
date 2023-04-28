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
        unsigned int nb_tour;
        int num_checkpoint=-1;

    public:
         /** \brief Constructeur par défaut \return Jeu */
        Jeu();
         /** \brief Constructeur avec paramètres \param nom_fichier Nom du fichier à charger \return Jeu */
        Jeu(string const & nom_fichier);
         /** \brief Destructeur */
        ~Jeu();

        //ajouter chargement voiture

        //fonctions de debug
         /** \brief Debug pour tenter de charger un terrain \return Terrain */
        Terrain &  getTerrain();
         /** \brief Debug pour tenter de charger une voiture (non fait) \return Voiture */
        Voiture & getVoiture(int i=0);
        

         /** \brief Définit le temps d'une frame \param tps Temps d'une frame */
        void setframe_time(float const & tps);
         /** \brief Charge un terrain \param nom_fichier Nom du fichier à charger, passé par référence */
        void ChargerTerrain(string const & nom_fichier);
         /** \brief Ajoute une voiture \param V Voiture à ajouter, passé par référence */
        void ajouterVoiture(Voiture const & V);
        

        //retirer le bool a terme ?
         /** \brief Met à jour le jeu \param action actions du joueur \return void */
        
        void update(ActionClavier const & action);

        int getNbTours() const { return (int)nb_tour; }

        
};



#endif