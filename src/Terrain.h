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

class Props
{   public:

        Vecteur pos;
        //!!la largeur et longueur sont la moitié de leur taille réelle -> calcul plus simple
        Vecteur hitbox;
        float rotation;//en radiant -> 0 = bas , pi/2 = droite, pi = haut, 3pi/2 = gauche
    private:
        Tip type;

    public:
        Props();
        Props(int px, int py, Tip t, float rot=0,float l=0, float L=0);
        
        float getX() const;
        float getY() const;
        Vecteur getPos() const;
        float getRotation() const;
        float getLarg() const;
        float getLong() const;
        Vecteur getHitbox() const;
        Tip getType() const;
        
        void prop_set_type(Tip t);
        void setProp(int px, int py, float rot=0, float nl=0, float nL=0);
        bool chargerJSON(json const & obj);
};

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