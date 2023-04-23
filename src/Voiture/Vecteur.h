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
        
        /** \brief Constructeur par défaut \return Vecteur */
        Vecteur();
        /** \brief Constructeur avec paramètres \param px Coordonnée x \param py Coordonnée y \return Vecteur */
        Vecteur(float px, float py); 
        /** \brief Opérateur d'affectation \param v Vecteur à copier, passé par référence \return Vecteur */
        Vecteur &operator=(const Vecteur & v); 
        
        bool operator==(const Vecteur a) const;

        /** \brief modifie un vecteur à partir d'une norme et d'un angle
         * \param norme Norme du vecteur
         * \param rotation Rotation du vecteur
         */
        void setVecteur(float norme, float rotation);
        /** \brief Retourne la norme du vecteur \return float */
        float getNorme() const; 
        /** \brief Retourne la norme au carré du vecteur \return float */
        float getNorme2() const;
        /** \brief Retourne la rotation du vecteur \return float */ 
        float getRotation() const; 
        /** \brief Tourne le vecteur \param angle Angle de rotation */
        void tourner(float angle=0); 
};
       

        
/** \brief Opérateur d'addition \param a Premier vecteur \param b Second vecteur \return Vecteur */
Vecteur operator+(Vecteur a, Vecteur b);
/** \brief Opérateur de soustraction \param a Premier vecteur \param b Second vecteur \return Vecteur */
Vecteur operator-(Vecteur a, Vecteur b);
/** \brief Opérateur de multiplication \param a Premier vecteur \param b Second vecteur \return Vecteur */
Vecteur operator*(Vecteur a, float b);  






#endif