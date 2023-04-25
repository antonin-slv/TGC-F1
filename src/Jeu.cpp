#include "Jeu.h"
#include <string>
#include "Collision.h"
#include "Voiture/Physique.h"
#include "Voiture/Vecteur.h"


Jeu::Jeu()
{   
    terrain=Terrain(100,30);
    nb_voit = 0;
    frame_time = 0.0167;
}


//ajouter dans le stockage un paramétrage de la voiture
Jeu::Jeu(string const & nom_fichier)
{   
    ChargerTerrain(nom_fichier);
    
    nb_voit = 0;
    frame_time = 0.0167;
}

void Jeu::setframe_time(float const & tps) { frame_time = tps; }


void Jeu::ChargerTerrain(string const & nom_fichier) { terrain.chargerJSON(nom_fichier); }

Jeu::~Jeu() { 
    cout<<"debut destruction jeu"<<endl;
    //tab_voit.clear();
    cout<<"fin destruction jeu"<<endl;
}

Terrain & Jeu::getTerrain() { return terrain; }

void Jeu::ajouterVoiture(Voiture const & V)
{   //on créé une voiture identique à V et on l'ajoute au tableau
    tab_voit.push_back(Voiture(V));
    nb_voit++;
}

Voiture & Jeu::getVoiture(int i) { return tab_voit[i]; }

void Jeu::update(ActionClavier const & Action)
{   tab_voit[0].action=Action;
    bool on_road = false;
    bool on_grass = false;
    for (int i=0; i<terrain.getNbProps(); i++)
    {   Props const & prop = terrain.getProp(i);
        switch(prop.getType())
        {   case Tip::checkpoint :
                if ((prop.getPos() - tab_voit[0].getPos()).getNorme2() < prop.getHitbox().getNorme2()) cout<<"checkpoint"<<endl;
                break;
            case Tip::finish :
                 if (testColPropVoit(prop, tab_voit[0])) cout<<"finish"<<endl;
                break;
            case Tip::grass :
                if (testColPropVoit(prop, tab_voit[0])) on_grass = true;
                break;
            default :
                if ((prop.getPos() - tab_voit[0].getPos()).getNorme2() < prop.getHitbox().getNorme2())
                {   on_road = true;}
                break;
        }  
    }
    if (!on_road||on_grass) tab_voit[0].on_grass(frame_time);

    tab_voit[0].update(frame_time);
}
