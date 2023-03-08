#include <iostream>
#include <fstream>
#include <string>
#include "Terrain.h"
#include "json.hpp"


using namespace std;
using json = nlohmann::json;

Props::Props()
{
    x = 0;
    y = 0;
    rotation = 0;
    type = nondef;
    l=0;
    L=0;
}

Props::Props(int px, int py, Tip t, float rot, float nl, float nL)
{
    x = px;
    y = py;
    rotation = rot;
    type = t;
    l=nl;
    L=nL;
};

void Props::setProp(int px, int py, float rot, float nl, float nL)
{
    x = px;
    y = py;
    rotation = rot;
    l=nl;
    L=nL;
}
void Props::prop_set_type(Tip t) { type = t; }

bool Props::chargerJSON(json obj)
{   if (obj.type() != json::value_t::object)
    {
        cout << "Prop corrompu" << endl;
        return false;
    }
    if (obj["x"].type() == json::value_t::null) x=0;
    else x = obj["x"];
    if (obj["y"].type() == json::value_t::null) y=0;
    else y = obj["y"];
    if (obj["rotation"].type() == json::value_t::null) rotation=0;
    else rotation = obj["rotation"];
    if (obj["l"].type() == json::value_t::null) l=0;
    else l = obj["l"];
    if (obj["L"].type() == json::value_t::null) L=0;
    else L = obj["L"];
    
    type=(Tip) obj["Type"];
    return true;
}

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
        tab_props[i].prop_set_type((Tip)(0));
    }
}

void Terrain::chargerJSON(string path){
    
    ifstream fichier(path);
    if (!fichier.good())
    {
        cout << "Erreur lors de l'ouverture du fichier" << endl;
        return;
    }

    json tab;
    
    fichier >> tab;

    nb_props = tab["Props"].size();
    int j=0;
    for (int i=0; i<nb_props; i++)
    {  
        if (tab_props[i-j].chargerJSON(tab["Props"][i])==false)
        {   
            j++;
        }
    }
    nb_props-=j;

    fichier.close();
}