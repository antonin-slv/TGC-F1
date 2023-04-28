#include "Jeu.h"
#include <string>
#include "Collision.h"
#include "Voiture/Physique.h"
#include "Voiture/Vecteur.h"
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"

using namespace std;
using namespace sf;


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

void Jeu::update(ActionClavier const & Action, Clock & temps_au_tour)
{   Voiture & Voit = tab_voit[0];
    Voit.action=Action;
    bool on_road = false;
    bool on_grass = false;
    //gestion des collisions avec les props

    for (int i=0; i<terrain.getNbProps(); i++)
    {   Props const & prop = terrain.getProp(i);
        switch(prop.getType())
        {   case Tip::checkpoint :
                break;
            case Tip::finish :
                 if ((Voit.getCheckpoint()==terrain.getOrdreCheckpoint().size()-1)&&testColPropVoit(prop, Voit))
                 {  Voit.passer_checkpoint(true);
                    nb_tour++;
                    cout<<"fini"<<endl;
                    temps_au_tour.restart();
                 }
                break;
            case Tip::grass :
                if (testColPropVoit(prop, Voit)) on_grass = true;
                break;
            default :
                if ((prop.getPos() - Voit.getPos()).getNorme2() < prop.getHitbox().getNorme2())
                {   on_road = true;}
                break;
        }  
    }
    //gestion des checkpoints
    num_checkpoint = Voit.getCheckpoint();
    if (testColPropVoit(terrain.getProp(terrain.getOrdreCheckpoint()[num_checkpoint+1]), Voit)) {
        Voit.passer_checkpoint();
        num_checkpoint = Voit.getCheckpoint();
        cout<<"checkpoint "<<num_checkpoint<<endl;
    }

    //si la voiture n'est pas sur la route/a une roue sur l'herbe, on la ralenti
    if (!on_road||on_grass) Voit.on_grass(frame_time);

    Voit.update(frame_time);
}
