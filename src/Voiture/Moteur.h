#ifndef MOTEUR_H
#define MOTEUR_H

#include <iostream>
#include <string>

using namespace std;

/**
 * @brief La classe Moteur
 * 
 */
class Moteur{

    private:

        string nom;
        int puissance;

    public:

        Moteur(); /** \brief Constructeur par défaut \return Moteur */
        Moteur(string n,int p); /** \brief Constructeur avec paramètres \param n Nom du moteur \param p Puissance du moteur \return Moteur */
        Moteur(const Moteur & M); /** \brief Constructeur par copie \param M Moteur à copier, passé par référence \return Moteur */

        string getNom(); /** \brief Retourne le nom du moteur \return string */
        int getPuissance(); /** \brief Retourne la puissance du moteur \return int */

};


#endif