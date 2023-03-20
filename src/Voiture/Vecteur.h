#ifndef _VECTEUR_H_
#define _VECTEUR_H_


#include <math.h>

/**
 * @brief La classe Vecteur
 */
class Vecteur
{   public :
        float x;
        float y;
        

        Vecteur(); /** \brief Constructeur par défaut \return Vecteur */
        Vecteur(float px, float py); /** \brief Constructeur avec paramètres \param px Coordonnée x \param py Coordonnée y \return Vecteur */
        Vecteur &operator=(const Vecteur & v); /** \brief Opérateur d'affectation \param v Vecteur à copier, passé par référence \return Vecteur */
        
        /** \brief Création d'un vecteur à partir de sa norme et de sa rotation
         * \param norme Norme du vecteur
         * \param rotation Rotation du vecteur
         */
        void setVecteur(float norme, float rotation);
        float getNorme() const; /** \brief Retourne la norme du vecteur \return float */
        float getNorme2() const; /** \brief Retourne la norme au carré du vecteur \return float */
        float getRotation() const; /** \brief Retourne la rotation du vecteur \return float */
        void tourner(float angle=0); /** \brief Tourne le vecteur \param angle Angle de rotation */
};
       

        

Vecteur operator+(Vecteur a, Vecteur b); /** \brief Opérateur d'addition \param a Premier vecteur \param b Second vecteur \return Vecteur */
Vecteur operator-(Vecteur a, Vecteur b); /** \brief Opérateur de soustraction \param a Premier vecteur \param b Second vecteur \return Vecteur */
Vecteur operator*(Vecteur a, float b);  /** \brief Opérateur de multiplication \param a Premier vecteur \param b Second vecteur \return Vecteur */





#endif