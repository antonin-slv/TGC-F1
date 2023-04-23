#ifndef _Editeur_H_
#define _Editeur_H_

#include "Terrain.h"
#include "Interface.h"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>


#include <vector>
#include <iostream>

using namespace std;
using namespace sf;


/**
 * @brief Classe de l'éditeur de terrain (non fait)
 * 
 */
class Editeur : public Terrain
{   
    private :
        Vector2f centre;
        float zoom;//10 par def
        int prop_selectionne;
        
        Interface interface;
        
    public :
        Editeur();
        void lier_window(RenderWindow & window);
        void zoom_(float z);
        void deplacer(float dx=0, float dy=0);

        void boucleEditeur(RenderWindow & window);
        


        void ajouter_prop(Tip t = Tip::road, Vector2f pos = Vector2f(0,0));
        void select_prop(bool plus_recent = true);
        void supprimer_prop(int i=-1);
        void deplacer_prop(float dx, float dy);

        void Init_props();
        void sauvegarder();
        bool charger(string path = "data/circuits/test1.json");

        void Init_ref_props();


        bool test_regression();
};


void map_pos_to_grid(Vecteur & pos);


#endif