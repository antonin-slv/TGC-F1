#include <iostream>
#include <fstream>
#include <string>
#include "Terrain.h"
#include "json.hpp"
#include <vector>

using namespace std;
using json = nlohmann::json;

Props::Props()
{
    pos.setVecteur(0,0);
    hitbox = pos;

    rotation = 0;
    type = nondef;
}

Props::Props(int px, int py, Tip t, float rot, float nl, float nL)
{
    pos.setVecteur(px,py);
    hitbox.setVecteur(nl,nL);
    rotation = rot;
    type = t;
};


float Props::getX() const { return pos.x; }

float Props::getY() const { return pos.y; }

float Props::getRotation() const { return rotation; }

float Props::getLarg() const { return hitbox.y; }

float Props::getLong() const { return hitbox.x; }

Tip Props::getType() const { return type; }

Vecteur Props::getPos() const { return pos; }

Vecteur Props::getHitbox() const { return hitbox; }

void Props::setProp(int px, int py, float rot, float lo, float La)
{   pos.setVecteur(px,py);
    hitbox.setVecteur(lo,La);
    rotation = rot;
}
void Props::prop_set_type(Tip t) { type = t; }

bool Props::chargerJSON(json const & obj)
{   if (obj.type() != json::value_t::object)
    {
        cout << "Prop corrompu" << endl;
        return false;
    }
    if (obj["x"].type() == json::value_t::null) pos.x=0;
    else pos.x = obj["x"];
    if (obj["y"].type() == json::value_t::null) pos.y=0;
    else pos.y = obj["y"];
    if (obj["rotation"].type() == json::value_t::null) rotation=0;
    else rotation = obj["rotation"];
    if (obj["l"].type() == json::value_t::null) hitbox.x=0;
    else hitbox.y = obj["l"];
    if (obj["L"].type() == json::value_t::null) hitbox.y=0;
    else hitbox.y = obj["L"];
    
    type=(Tip) obj["Type"];
    return true;
}

Terrain::Terrain()
{
    largeur = 1000;
    longueur = 1000;
    nb_props = 0;
}

Terrain::Terrain(int l, int h, int nb)
{   
    largeur = l;
    longueur = h;
    nb_props = nb;
    vector<Props> tab_props(nb_props);
}

int Terrain::getLargeur() const { return largeur; }
int Terrain::getLongueur() const { return longueur; }
int Terrain::getNbProps() const { return nb_props; }

Terrain::~Terrain()
{  tab_props.clear();
}

void Terrain::chargerJSON(string const & path){
    
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
    Props temp;
    for (int i=0; i<nb_props; i++)
    {  
        if (temp.chargerJSON(tab["Props"][i]))
        {   tab_props.push_back(temp);
            cout<<"prop "<<i-j<<" chargé"<<endl;
        }
        else j++;
    }
    nb_props-=j;
    if (j> 0)cout<<j<<" props corrompus"<<endl;
    fichier.close();
}

Props & Terrain::getProp(int i)
{
    assert(i < nb_props);
    return tab_props[i];
}