#ifndef _Editeur_H_
#define _Editeur_H_

#include "Terrain.h"

/**
 * @brief Classe de l'éditeur de terrain (non fait)
 * 
 */
class Editeur : public Terrain
{   
    private :
        float x, y;
        int zoom;//10 par def
    public : 
        //Editeur() : Terrain() {x = 0; y = 0; zoom = 10;}; /** @brief Constructeur par défaut (non fait) */

};



#endif