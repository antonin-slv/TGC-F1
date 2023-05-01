#ifndef _TERRAIN_H_
#define _TERRAIN_H_

#include <iostream>
#include <bits/stdc++.h>
#include <fstream>
#include <string>
#include <vector>
#include "External/json.hpp"
#include "Voiture/Vecteur.h"

using namespace std;
using json = nlohmann::json;

/** @brief Les "tip" (types) de props */
enum Tip : int
{   nondef=0,
    finish=1,
    grass=2,
    road=3,
    road_kerb_a=4,
    road_kerb_m=5,
    road_kerb_z=6,
    turn1=7,
    turn2=8,
    turn3=9,
    turn4=10,
    checkpoint=11,
    end_of_class=12,   
};

/** 
 * @brief La classe Props
 * Modules de base d'un terrain
 */
class Props
{   private:

        Vecteur pos;
        //!!la largeur et longueur sont la moitié de leur taille réelle -> calcul plus simple
        Vecteur hitbox;
        float rotation;//en radiant -> 0 = bas , pi/2 = droite, pi = haut, 3pi/2 = gauche
        Tip type;

    public:
        /** \brief Constructeur par défaut \return Props */
        Props(); 

        /** \brief Constructeur avec paramètres
         * \param px Position en x
         * \param py Position en y
         * \param t Type de props
         * \param rot Rotation du props
         * \param l Largeur du props
         * \param L Longueur du props
         * \return Props
         */
        Props(int px, int py, Tip t, float rot=0,float l=0, float L=0);
        
        /** \brief Retourne la position en x \return float */
        float getX() const;
        /** \brief Retourne la position en y \return float */ 
        float getY() const;
        /** \brief Retourne le vecteur position \return Vecteur */
        Vecteur getPos() const;
        /** \brief Retourne la rotation \return float */ 
        float getRotation() const;
        /** \brief Retourne la largeur \return float */
        float getLarg() const;
        /** \brief Retourne la longueur \return float */
        float getLong() const;
        /** \brief Retourne le vecteur hitbox \return Vecteur */
        Vecteur getHitbox() const;
        /** \brief Retourne le type \return Tip */
        Tip getType() const; 
        
        /** \brief Remplace le type \param t Nouveau Type */
        void set_type(Tip t); 

        /** \brief permet de donner une nouvelle hitbox \param hitbox nouvelle hitbox*/
        void setHitbox(Vecteur const & hitbox);
        /** \brief permet de donner une nouvelle rotation \param rot nouvelle rotation*/
        void setRot(float rot=0);
        /** \brief permet de donner une nouvelle position \param pos nouvelle position*/
        void setPos(Vecteur const & pos);

        /** \brief Charge les données du prop depuis un fichier JSON
         * \param obj Objet JSON \return booléen vrai si la fonction a marchée */
        bool chargerJSON(json const & obj); 
};

/** 
 * @brief La classe du Terrain
 * 
 */
class Terrain
{   protected:
        int largeur;//en m
        int longueur;//en m
        
        int nb_props;
        vector<Props> tab_props;//tableaux de props
        vector<int> ordre_checkpoint;//le ième élément est le numéro du props qui est le ième checkpoint
        Props prop_undef;

    public:
        /** \brief Constructeur par défaut \return Terrain */
        Terrain();
        /** \brief Constructeur avec paramètres
         * \param l Largeur du terrain
         * \param h Longueur du terrain
         * \param nb Nombre de props
         * \return Terrain
         */
        Terrain(int l, int h, int nb=1);
        /** \brief Destructeur */
        ~Terrain();

        /** \brief Retourne la largeur du terrain \return int */
        int getLargeur() const;
        /** \brief Retourne la longueur du terrain \return int */
        int getLongueur() const;
        /** \brief Retourne le nombre de props du terrain \return int */
        int getNbProps() const;

        /** \brief Retourne le ième props du terrain \param i Numéro du props \return Props */
        Props const & getProp(int i);

        /** \brief Charge les données depuis un fichier JSON \param path Chemin du fichier */
        bool chargerJSON(string const & path);

        /** \brief Retourne le numéro du prop \param pos Position \return rang du prop si il existe, -1 sinon */
        int getProp(Vecteur const & pos);
        /** \brief Renvoie une référence vers la ligne d'arrivée \return référence vers la ligne arrivée*/
        Props const & getLigneArrivee();
        
        /** \brief Retourne le vector des props \return vector<Props> */
        vector<Props> const getTabProps() const;
        /** \brief Retourne le vector contenant les checkpoints dans l'ordre \return vector<int> */
        vector<int> const &getOrdreCheckpoint() const;
    
};




#endif