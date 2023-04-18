#ifndef _Editeur_H_
#define _Editeur_H_

#include "Terrain.h"


#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

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
        Vecteur centre;
        int zoom;//10 par def
        int prop_selectionne;
        vector<Props> ref_props;
    public :
        Editeur();
        void afficher();
        void zoom_in();
        void zoom_out();
        void deplacer(float dx=0, float dy=0);

        void boucleEditeur(RenderWindow & window);
        


        void ajouter_prop(Tip t = Tip::Route);
        void select_prop();
        void supprimer_props();

        void Init_props();
        void sauvegarder();
        bool charger();

        bool test_regression();
};



#endif