#include "Editeur.h"



Editeur::Editeur()
{
    x = 0;
    y = 0;
    zoom = 10;
}

Editeur::Editeur(float x, float y, int zoom)
{
    this->x = x;
    this->y = y;
    this->zoom = zoom;
}

void Editeur::afficher()
{

}

void Editeur::zoom_in()
{   
    zoom++;
}

void Editeur::zoom_out()
{   if(zoom > 1) zoom--;
}

void Editeur::deplacer(float dx, float dy)
{
    x += dx;
    y += dy;
}

void Editeur::charger()
{   string path = "data/circuits/test.json"
    void chargerJSON(path);
}

void Editeur::sauvegarder()
{   string path = "data/circuits/test1.json"

    ofstream fichier(path);

    json j =
    {
    "Props" : [
    ]
    };

    for (int i = 0; i < nb_props; i++)
    {   j["props"][i]["x"] = props[i].getX();
        j["props"][i]["y"] = props[i].getY();
        j["props"][i]["rotation"] = props[i].getRotation();
        j["props"][i]["type"] = props[i].getType();
        j["props"][i]["l"] = props[i].getLongueur();
        j["props"][i]["L"] = props[i].getLargeur();
    }

    fichier << j;

    fichier.close();
}

void Editeur::selectionner_prop()
{
    //TODO
}