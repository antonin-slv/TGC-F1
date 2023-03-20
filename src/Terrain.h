#ifndef _TERRAIN_H_
#define _TERRAIN_H_

#include <iostream>
#include <bits/stdc++.h>
#include <fstream>
#include <string>
#include <vector>
#include "json.hpp"
#include "Voiture/Vecteur.h"

using namespace std;
using json = nlohmann::json;

/** @brief Les "tip" (types) de props */
enum Tip : int
{   nondef=0,
    arbre=1,
    gradin=2,
    Route=10,
    route_b_g=15,
    route_b_d=14,
    route_h_g=13,
    route_h_d=12,
    route_g_d=11,
    route_h_b=16,   
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
        Props(); /** \brief Constructeur par défaut \return Props */

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
        
        float getX() const; /** \brief Retourne la position en x \return float */
        float getY() const; /** \brief Retourne la position en y \return float */
        Vecteur getPos() const; /** \brief Retourne la position \return Vecteur */
        float getRotation() const; /** \brief Retourne la rotation \return float */
        float getLarg() const; /** \brief Retourne la largeur \return float */
        float getLong() const; /** \brief Retourne la longueur \return float */
        Vecteur getHitbox() const; /** \brief Retourne la hitbox \return Vecteur */
        Tip getType() const; /** \brief Retourne le type \return Tip */
        
        void prop_set_type(Tip t); /** \brief Donne le type \param t Type \return void */

        /** \brief Donne la position
         * \param px Position en x
         * \param py Position en y
         */
        void setProp(int px, int py, float rot=0, float nl=0, float nL=0);
        bool chargerJSON(json const & obj); /** \brief Charge les données depuis un fichier JSON \param obj Objet JSON \return bool */
};

/** 
 * @brief La classe du Terrain
 * 
 */
class Terrain
{   private:
        int largeur;//en m
        int longueur;//en m
        
        int nb_props;

    public:
        vector<Props> tab_props;
        Terrain();
        Terrain(int l, int h, int nb=1);
        ~Terrain();

        int getLargeur() const;
        int getLongueur() const;
        int getNbProps() const;

        Props & getProp(int i);

        void chargerJSON(string const & path);
        void afficher_txt();
    
};




#endif