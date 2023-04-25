#ifndef _Menu_H_
#define _Menu_H_

#include <iostream>
#include"Interface.h"

using namespace std;

class Bouton{
    private:
        RectangleShape rectangle;
        Text texte;
        Font font;
    
    public:
        Bouton(string txt, Font font, int char_size, int y, int width, int height);
};

class Menu{
    private:
        
    public:
        int boucleMenu(RenderWindow & window, int & volume, float & decalage);
};

#endif