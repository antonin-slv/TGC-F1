#ifndef VOITURE_H
#define VOITURE_H

#include "Moteur.h"
#include "Roues.h"
#include "Physique.h"
#include "Vecteur.h"

#include <iostream>
#include <math.h>

using namespace std;


struct ActionClavier
{
    bool freine=false;
    bool gauche=false;
    bool droite=false;
    bool accelere=false;
};


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
        
        int numero_checkpoint=-1;

        float poids, coef_aero;

        /** \brief Actualise la vitesse de la voiture \param dt Delta temps */
        void calculVitesse(float dt=1); 
        /** \brief Actualise la position de la voiture (plus précis) \param dt Delta temps */
        void calculPosition_precis(float dt=1); 

    public:
        //booléens de controle de la voiture
        ActionClavier action;
        
        /** \brief Actualise la voiture \n !!penser à mettre a jour les action avant  \param dt Delta temps */
        void update(float dt=1/60);

        /** \brief Remplace la rotation de la voiture par \param angle_  nouvel angle*/
        void setRotation(float angle_);
        /** \brief Envoie la voiture en \param pos_ nouvelle position*/
        void setPos(Vecteur pos_);
        /** \brief Remplace la hitbox de la voiture \param hitbox_ nouvelle hitbox*/
        void setHitbox(Vecteur hitbox_);

        /** \brief Constructeur par défaut \return Voiture */
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
        /** \brief Retourne l'accélération de la voiture \return float */
        float getAcceleration() const;
        /** \brief Retourne la vitesse de la voiture \return float */
        float getVitesse() const;
        /** \brief Retourne l'angle de la voiture \return float */
        float getAngle() const;
        /** \brief Retourne le poids de la voiture \return float */
        float getPoids() const;
        /** \brief Retourne le coefficient aérodynamique de la voiture \return float */
        float getCoefAero() const;
        /** \brief Retourne le vecteur position de la voiture \return Vecteur */
        Vecteur getPos() const; 

        /** \brief Retourne le vecteur hitbox de la voiture \return Vecteur */
        Vecteur getHitbox() const;
        
        //bool chargerJSON(json const & obj); 

        /** \brief met a jour l'accélération de la voiture \param proportion entre 0 et 1 */
        void avancer(float proportion=1);
        /** \brief met a jour l'accélération de la voiture \param proportion entre 0 et 1 */
        void new_freiner(float proportion=1); 
        /** \brief met a jour l'accélération de la voiture quand il n'y a pas d'action */
        void new_ralentir(float dt=1/60); 
        
        
        
        /** \brief Tourne la voiture
         * \param angle_roue_rad Angle de rotation des roues
         * \param dt Temps durant lequel la voiture est tournée
         */
        void tourner_var(float angle_roue_rad,float dt=1);
        /** \brief Tourne la voiture vers la gauche \param dt Temps durant lequel la voiture est tournée */
        void tourner_g(float dt=1/60);
        /** \brief Tourne la voiture vers la droite \param dt Temps durant lequel la voiture est tournée */ 
        void tourner_d(float dt=1/60); 

        /** \brief Gère les collisions avec les murs
         * \param diff Vecteur de différence entre la voiture et le mur
         * \param anglemur Angle du mur
         */
        void crash(Vecteur diff, float anglemur);

        /** \brief ralentit la voiture quand elle est sur l'herbe\n à utiliser dans l'update \param dt temps d'une frame */
        void on_grass(float dt=1/60);

        /** \brief fait passer le checkpoint à la voiture \param arrivee true si on est sur la ligne d'arrivée*/
        void passer_checkpoint(bool arrivee=false);
        /** \brief retourne le numéro du dernier checkpoint passé \return -1 si c'est la ligne d'arrivée */
        int getCheckpoint() const;

        /** \brief réinitialise la voiture \param pos nouvelle position \param angle nouvel angle */
        void restart(Vecteur pos=Vecteur(0,0), float angle=0);
};

#endif