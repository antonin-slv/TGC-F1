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
        /** \brief Nom du moteur (inutilisé)*/
        string nom;
        /** \brief Puissance du moteur */
        int puissance;

    public:
         /** \brief Constructeur par défaut \return Moteur */
        Moteur();
         /** \brief Constructeur avec paramètres \param n Nom du moteur \param p Puissance du moteur \return Moteur */
        Moteur(string n,int p);
        /** \brief Constructeur par copie \param M Moteur à copier, passé par référence \return Moteur */
        Moteur(const Moteur & M); 
        /** \brief Retourne le nom du moteur \return string */
        string getNom();
        /** \brief Retourne la puissance du moteur \return int */ 
        int getPuissance(); 

};


#endif