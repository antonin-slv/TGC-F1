#ifndef ROUES_H
#define ROUES_H

#include <iostream>
#include <string>

using namespace std;

/**
 * @brief La classe Roues (utile seulement pour l'initialisation d'une voiture)
 * 
 */
class Roues{

    private:
        /** \brief Nom des roues (inutilisé)*/
        string nom;
        /** \brief Orientation des roues (inutilisé)*/
        float orientation;
        /** \brief Grip des roues (inutilisé)*/
        float grip;

    public:

        /** \brief Constructeur par défaut \return Roues */
        Roues(); 

        /** \brief Constructeur avec paramètres
         * \param n Nom des roues
         * \param o Orientation des roues
         * \param g Grip des roues
         * \return Roues
         */
        Roues(string n,float o, float g);
        /** \brief Constructeur par copie \param R Roues à copier, passé par référence \return Roues */
        Roues(const Roues & R); 

        /** \brief Retourne le nom des roues \return string */
        string getNom();
        /** \brief Retourne l'orientation des roues \return float */
        float getOrientation();
        /** \brief Retourne le grip des roues \return float */
        float getGrip(); 
};

#endif