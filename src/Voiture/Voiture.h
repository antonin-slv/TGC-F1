#ifndef VOITURE_H
#define VOITURE_H

#include "Moteur.h"
#include "Roues.h"
#include "Physique.h"
#include "Vecteur.h"

#include <iostream>
#include <math.h>

using namespace std;

/**
 * @brief La classe Voiture
 * 
 */
class Voiture {

    private:

        Moteur mot;
        Roues roue;

        Vecteur position;
        Vecteur hitbox; //!!la largeur et longueur sont la moitié de leur taille réelle -> calcul plus simple

        float acceleration;
        float vitesse;
        float angle;
        
        float poids, coef_aero;

        /** \brief Actualise l'accélération de la voiture \param dt Delta temps \param theta Angle de la voiture */
        void calculAcc(float dt=1,float theta=1);
        /** \brief Actualise la vitesse de la voiture \param dt Delta temps */
        void calculVitesse(float dt=1); 
        /** \brief Actualise la position de la voiture \param dt Delta temps */
        void calculPosition(float dt=1); 
        /** \brief Actualise la position de la voiture (plus précis) \param dt Delta temps */
        void calculPosition_precis(float dt=1); 

    public:
        /** \brief Constructeur par défaut */
        Voiture(); 
        
        /** \brief Constructeur avec paramètres
         * \param m Moteur de la voiture
         * \param r Roues de la voiture
         * \param poi Poids de la voiture
         * \param coef Coefficient aérodynamique de la voiture
         * \param largeur Largeur de la voiture
         * \param longu Longueur de la voiture
         * \param orient Orientation de la voiture
         * \param vit Vitesse de la voiture
         * \param x Position x de la voiture
         * \param y Position y de la voiture
         * \param acc Accélération de la voiture
         * \return Voiture
         */
        Voiture(const Moteur & m,const Roues & r, float poi, float coef,float largeur,float longu, float orient=M_PI/2, float vit=0, float x=0,
                float y=0, float acc=0);
        /** \brief Constructeur par copie \param V Voiture à copier, passée par référence \return Voiture */
        Voiture(const Voiture & V);
         /** \brief Destructeur de Voiture */
        ~Voiture();

        /** \brief Retourne le moteur de la voiture \return Moteur */
        const Moteur & getMoteur() const;
        /** \brief Retourne les roues de la voiture \return Roues */ 
        const Roues & getRoues() const;
        /** \brief Retourne la vitesse de la voiture \return float */
        float getVitesse() const;
        /** \brief Retourne l'angle de la voiture \return float */
        float getAngle() const;
        /** \brief Retourne le poids de la voiture \return float */
        float getPoids() const;
        /** \brief Retourne le coefficient aérodynamique de la voiture \return float */
        float getCoefAero() const;
        /** \brief Retourne la position x de la voiture \return float */
        float getX() const;
         /** \brief Retourne la position y de la voiture \return float */
        float getY() const;
        /** \brief Retourne le vecteur position de la voiture \return Vecteur */
        Vecteur getPos() const; 

        /** \brief Retourne le vecteur hitbox de la voiture \return Vecteur */
        Vecteur getHitbox() const;
        /** \brief Retourne la largeur de la voiture \return float */
        float getLargeur() const; 
        /** \brief Retourne la longueur de la voiture \return float */
        float getLongueur() const; 

        /** \brief Accélère la voiture \param dt Temps durant lequel la voiture est accélérée */
        void accelerer(float dt=1);
        /** \brief Ralentit la voiture \param dt Temps durant lequel la voiture est ralentie */
        void ralentir(float dt=1);
        /** \brief Freine la voiture \param dt Temps durant lequel la voiture est freinée */
        void freiner(float dt=1); 
        
        /** \brief Tourne la voiture
         * \param angle_roue_rad Angle de rotation des roues
         * \param dt Temps durant lequel la voiture est tournée
         */
        void tourner_var(float angle_roue_rad,float dt=1);
        /** \brief Tourne la voiture vers la gauche \param dt Temps durant lequel la voiture est tournée */
        void tourner_g(float dt=1);
        /** \brief Tourne la voiture vers la droite \param dt Temps durant lequel la voiture est tournée */ 
        void tourner_d(float dt=1); 

        /** \brief Gère les collisions avec les murs
         * \param diff Vecteur de différence entre la voiture et le mur
         * \param anglemur Angle du mur
         */
        void crash(Vecteur diff, float anglemur);

};

#endif