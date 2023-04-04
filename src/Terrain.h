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
    arbre=1,
    gradin=2,
    Route=3,
    route_b_g=4,
    route_b_d=5,
    route_h_g=6,
    route_h_d=7,
    route_g_d=8,
    route_h_b=9,
    end_of_class=10   
};

/** 
 * @brief La classe Props
 * 
 */
class Props
{   public:

        Vecteur pos;
        //!!la largeur et longueur sont la moitié de leur taille réelle -> calcul plus simple
        Vecteur hitbox;
        float rotation;//en radiant -> 0 = bas , pi/2 = droite, pi = haut, 3pi/2 = gauche
    private:
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
        
        /** \brief Donne le type \param t Type \return void */
        void prop_set_type(Tip t); 

        /** \brief Donne la position
         * \param px Position en x
         * \param py Position en y
         */
        void setProp(int px, int py, float rot=0, float nl=0, float nL=0);
        /** \brief Charge les données depuis un fichier JSON \param obj Objet JSON \return bool */
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
        vector<Props> tab_props;

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

        /** Retourne le ième props du terrain \param i Numéro du props \return Props */
        Props & getProp(int i);

        /** Charge les données depuis un fichier JSON \param path Chemin du fichier */
        bool chargerJSON(string const & path);
        /** \brief Affiche le terrain en TXT */
        void afficher_txt();
    
};




#endif