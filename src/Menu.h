#ifndef _Menu_H_
#define _Menu_H_

#include <iostream>
#include"Interface.h"

using namespace std;

class Menu{
    private:
        Interface interface;
        string chemin;

    public:
        int boucleMenu(RenderWindow & window);
};

 /** \brief Si le jeu est en pause ou non \return bool */
bool Menu_Pause(void);
 /** \brief Si le jeu est au menu principal ou non \return bool*/
bool Menu_Principal(void);

#endif