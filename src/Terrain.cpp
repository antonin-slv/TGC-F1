#include "Terrain.h"


Props::Props()
{
    x = 0;
    y = 0;
    rotation = 0;
    type = nondef;
}

Props::Props(int px, int py, Tip t, float rot)
{
    x = px;
    y = py;
    rotation = rot;
    type = t;
};

void Props::prop_set_type(Tip t) { type = t; }

Terrain::Terrain()
{
    largeur = 1000;
    longueur = 1000;
    nb_props = 0;
    tab_props = nullptr;
}

Terrain::Terrain(int l, int h, int nb)
{
    largeur = l;
    longueur = h;
    nb_props = nb;
    tab_props = new Props[nb_props];
    
}

Terrain::~Terrain()
{
    if(tab_props != nullptr) delete [] tab_props;
}

void Terrain::Initialiser()
{
    for (int i=0; i<nb_props; i++)
    {
        tab_props[i].x = rand()%largeur;
        tab_props[i].y = rand()%longueur;
        tab_props[i].prop_set_type((Tip)(rand()%4));
    }
}