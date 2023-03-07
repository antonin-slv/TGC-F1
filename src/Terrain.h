#ifndef _TERRAIN_H_
#define _TERRAIN_H_

#include <iostream>
#include <bits/stdc++.h>
#include <fstream>
#include <string>
#include "json/json.h"

using namespace std;


enum Tip : int
{   nondef=0,
    arbre=1,
    gradin=2,
    route_b_g=15,
    route_b_d=14,
    route_h_g=13,
    route_h_d=12,
    route_g_d=11,
    route_h_b=10,
    
    
};


class Props
{   public:
        int x;//en m
        int y;//en m
        float rotation;//en radiant -> 0 = bas , pi/2 = droite, pi = haut, 3pi/2 = gauche
    private:
        Tip type;

    public:
        Props();
        Props(int px, int py, Tip t, float rot=0);
        
        void prop_set_type(Tip t);

};

class Terrain
{   private:
        int largeur;//en m
        int longueur;//en m
        Props * tab_props;
        int nb_props;

    public:

        Terrain();
        Terrain(int l, int h, int nb=1);
        ~Terrain();
        void Initialiser();
        void chargerJSON(string path);
    
};




#endif