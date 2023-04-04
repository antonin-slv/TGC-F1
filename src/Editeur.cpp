#include "Editeur.h"



Editeur::Editeur()
{
    x = 0;
    y = 0;
    zoom = 10;
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

bool Editeur::charger()
{   string path = "data/circuits/test1.json";
    return chargerJSON(path);
}

void Editeur::sauvegarder()
{   string path = "data/circuits/test1.json";

    ofstream fichier;

    json j;

    for (int i = 0; i < nb_props; i++)
    {   j["props"][i]["x"] = tab_props[i].getX();
        j["props"][i]["y"] = tab_props[i].getY();
        j["props"][i]["rotation"] = tab_props[i].getRotation();
        j["props"][i]["type"] = tab_props[i].getType();
        j["props"][i]["l"] = tab_props[i].getLong();
        j["props"][i]["L"] = tab_props[i].getLarg();
    }

    fichier.open(path);

    fichier << j.dump(4);

    fichier.close();
}

void Editeur::Init_props()
{   int i=0;
    while (i++ != Tip::end_of_class)
    {   ref_props.push_back(Props());
        ref_props[i].prop_set_type((Tip) i);
    }
    //TODO
}


void Editeur::ajouter_prop(Tip t)
{   tab_props.push_back(ref_props[t]);
    nb_props++;
    prop_selectionne = nb_props-1;
    //TODO
}

void Editeur::select_prop()
{   
    if(prop_selectionne <= 0) prop_selectionne = nb_props;
    prop_selectionne--;
}

void Editeur::supprimer_props()
{   //tab_props.erase(prop_selectionne);
    nb_props--;
    prop_selectionne--;
}

bool Editeur::test_regression()
{   charger();
    Init_props();
    sauvegarder();
    //TODO
    return true;
}

