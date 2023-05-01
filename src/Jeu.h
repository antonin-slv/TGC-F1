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
 * @brief Classe du jeu sans interface graphique
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
         /** \brief Constructeur par défaut, figuratif \return Jeu */
        Jeu();
         /** \brief Constructeur avec le lien du Terrain à charger
          *  \param path lien du circuit à charger \return Jeu */
        Jeu(string path);
         /** \brief Destructeur 
          * explicite la destruction des voitures
         */
        ~Jeu();
        
         /** \brief Renvoie une référence au terrain \return Terrain du jeu*/
        Terrain const & getTerrain();
         /** \brief renvoie la ieme voiture du jeu 
          *  \param i indice de la voiture (0 par défaut, c'est celle du joueur)
          * \return Voiture choisie*/
        Voiture & getVoiture(int i=0);
        /** \brief Renvoie le nombre de tours effectués par le joueur \return Nombre de tours */
        int getNbTours() const { return (int)nb_tour; }
        
        /** \brief Réinitialise le niveau (voitures, checkpoint, tours...)
         * chaque voiture est aussi réinitialisée (position, vitesse, rotation; numéro de checkpoint)
         * */ 
        void restart();

        /** \brief Définit le temps d'une frame \param tps Temps d'une frame */
        void setframe_time(float const & tps);
        /** \brief Charge un terrain, pose la voiture au bon endroit.
          *  \param path chemin vers le fichier */
        void ChargerTerrain(string path, int nb_tours=3);
        /** \brief Ajoute une voiture \param V Voiture à ajouter, passé par référence */
        void ajouterVoiture(Voiture const & V); 

        /** \brief Met à jour le jeu \param action actions du joueur
         * \return 1 si le joueur a gagné. -1 si un tour est effectué. 0 sinon  */
        int update(ActionClavier const & action);
        
};



#endif