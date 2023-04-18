#include "Editeur.h"



Editeur::Editeur()
{   centre = Vecteur(0,0);
    zoom = 10;
}

void Editeur::afficher()
{

}

void Editeur::boucleEditeur(RenderWindow & window)
{   charger();
    Event event;
    while (window.pollEvent(event))
    {   if (event.type == Event::Closed) return;
        if (event.type == Event::KeyPressed)
        {   if (event.key.code == Keyboard::Escape) return;
            if (event.key.code == Keyboard::Z)
                deplacer(0, 1);
            if (event.key.code == Keyboard::S)
                deplacer(0, -1);
            if (event.key.code == Keyboard::Q)
                deplacer(-1, 0);
            if (event.key.code == Keyboard::D)
                deplacer(1, 0);
            if (event.key.code == Keyboard::A)
                select_prop();
            
            /*
            if (event.key.code == Keyboard::E)
                ajouter_prop();
            if (event.key.code == Keyboard::R)
                supprimer_props();
            */
        }
    }

    

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
    centre.x += dx;
    centre.y += dy;
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
    centre=tab_props[prop_selectionne].getPos();
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

