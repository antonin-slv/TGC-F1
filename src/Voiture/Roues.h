#ifndef ROUES_H
#define ROUES_H

#include <iostream>
#include <string>

using namespace std;

/**
 * @brief La classe Roues
 * 
 */
class Roues{

    private:
    
        string nom;
        float orientation, grip;

    public:

        Roues(); /** \brief Constructeur par défaut \return Roues */

        /** \brief Constructeur avec paramètres
         * \param n Nom des roues
         * \param o Orientation des roues
         * \param g Grip des roues
         * \return Roues
         */
        Roues(string n,float o, float g);
        Roues(const Roues & R); /** \brief Constructeur par copie \param R Roues à copier, passé par référence \return Roues */

        string getNom(); /** \brief Retourne le nom des roues \return string */
        float getOrientation(); /** \brief Retourne l'orientation des roues \return float */
        float getGrip(); /** \brief Retourne le grip des roues \return float */
};

#endif