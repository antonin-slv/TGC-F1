#ifndef _Editeur_H_
#define _Editeur_H_
#include "Terrain.h"

class Editeur : public Terrain
{   
    private :
        float x, y;
        int zoom;//10 par def
    public :
        Editeur();
        ~Editeur();
        
        //pas fait
        Editeur(String nom);
        

}



#endif