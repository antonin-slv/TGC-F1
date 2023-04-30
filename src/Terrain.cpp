#include "Terrain.h"

#include "External/json.hpp"

#include <iostream>
#include <fstream>
#include <string>
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

void  Props::setHitbox(Vecteur const & hitbox_) { hitbox=hitbox_; }

void  Props::setRot(float rot) { rotation = rot; }

void  Props::setPos(Vecteur const & pos_) { pos= pos_; }

void Props::set_type(Tip t) { type = t; }

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
    else hitbox.x = obj["l"];
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

Terrain::Terrain(int lon, int haut, int nb)
{   
    largeur = haut;
    longueur = lon;
    nb_props = nb;
    vector<Props> tab_props(nb_props);
}

int Terrain::getLargeur() const { return largeur; }
int Terrain::getLongueur() const { return longueur; }
int Terrain::getNbProps() const { return nb_props; }

Terrain::~Terrain(){

    tab_props.clear();
}

bool Terrain::chargerJSON(string const & path){
    
    tab_props.clear();
    ordre_checkpoint.clear();
    nb_props=0;

    ifstream fichier(path);
    if (!fichier.good())
    {   nb_props = 0;
        cout << "Erreur lors de l'ouverture du fichier" << endl;
        return 0;
    }

    json tab;
    
    fichier >> tab;

    nb_props = tab["Props"].size();
    int j=0;
    Props temp;
    largeur = 0;
    longueur = 0;
    for (int i=0; i<nb_props; i++) //charge les props dans le tableau de props
    {  
        if (temp.chargerJSON(tab["Props"][i])) {
            tab_props.push_back(temp);
            //définit la largeur et la longueur du terrain à partir des props
            if (abs(temp.getY()) > largeur) largeur = abs(temp.getY());
            if (abs(temp.getX()) > longueur) longueur = abs(temp.getX());
        } else j++;
    }
    largeur+=50;
    longueur+=50;
    //parcour le tableau d'ordre des checkpoints du Json(l'élément 1 => le ième prop est un le 'it[i]' ème checkpoint 
    //et ajoute les pointeurs vers les props correspondants dans le tableau de pointeurs vers les checkpoints
 
    for (auto it = tab["ordre_checkpoints"].begin(); it != tab["ordre_checkpoints"].end(); it++)
    {       ordre_checkpoint.push_back(*it);
    }
    

    nb_props-=j;
    if (j> 0)cout<<j<<" props corrompus"<<endl;
    fichier.close();
    cout<<"Terrain chargé"<<endl;
    return 1;
}

Props const & Terrain::getProp(int i)
{
    assert(i < (int) tab_props.size());
    return tab_props[i];
}

vector <Props> const Terrain::getTabProps() const
{
    return tab_props;
}

int Terrain::getProp(Vecteur const & pos)
{
    for (int i=0; i<nb_props; i++)
    {   if (pos == tab_props[i].getPos())
        {   return i;
        }
    }
    return -1;
}
Props const & Terrain::getLigneArrivee()
{
    
    for (int j=0; j<nb_props; j++)
    {   if (tab_props[j].getType() == Tip::finish) return tab_props[j];
    }
    return prop_undef;
}

vector <int> const & Terrain::getOrdreCheckpoint() const
{
    return ordre_checkpoint;
}