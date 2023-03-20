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
{   private :
        Terrain terrain;
        vector<Voiture> tab_voit;
        float frame_time;
        int nb_voit;

    public:
        Jeu(); /** \brief Constructeur par défaut \return Jeu */
        Jeu(string const & nom_fichier); /** \brief Constructeur avec paramètres \param nom_fichier Nom du fichier à charger \return Jeu */
        ~Jeu(); /** \brief Destructeur */

        //ajouter chargement voiture

        //fonctions de debug
        Terrain &  getTerrain(); /** \brief Debug pour tenter de charger un terrain \return Terrain */
        Voiture & getVoiture(int i=0); /** \brief Debug pour tenter de charger une voiture (non fait) \return Voiture */
        


        void setframe_time(float const & tps); /** \brief Définit le temps d'une frame \param tps Temps d'une frame */
        void ChargerTerrain(string const & nom_fichier); /** \brief Charge un terrain \param nom_fichier Nom du fichier à charger, passé par référence */
        void AjouterVoiture(Voiture const & V); /** \brief Ajoute une voiture \param V Voiture à ajouter, passé par référence */
        

        //retirer le bool a terme ?
        int update(char const & touche); /** \brief Met à jour le jeu \param touche Touche appuyée \return int */
    
};



#endif