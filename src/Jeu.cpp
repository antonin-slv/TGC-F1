#include "Jeu.h"
#include <string>
#include "Collision.h"
#include "Voiture/Physique.h"
#include "Voiture/Vecteur.h"


Jeu::Jeu()
{   
    terrain=Terrain(100,30);
    nb_voit = 1;
    tab_voit = vector<Voiture>(nb_voit);
    frame_time = 0.0167;
}


//ajouter dans le stockage un paramétrage de la voiture
Jeu::Jeu(string const & nom_fichier)
{   
    ChargerTerrain(nom_fichier);
    nb_voit = 1;
    tab_voit = vector<Voiture>(nb_voit);
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

void Jeu::AjouterVoiture(Voiture const & V)
{   //on créé une voiture identique à V et on l'ajoute au tableau
    tab_voit.push_back(Voiture(V));
    nb_voit++;
}

Voiture & Jeu::getVoiture(int i) { return tab_voit[i]; }


int Jeu::update(char const & touche)
{   //on met à jour la position de la voiture
    //tab_voit[0].update(frame_time, touche);

    switch (touche)
    {   //on met à jour la direction de la voiture en fonction de la touche appuyée
    
    case 'z':
        tab_voit[0].avancer(frame_time);
        break;
    case 'q':
        tab_voit[0].tourner_g(frame_time);
        
        break;
    case 'd' :
        tab_voit[0].tourner_d(frame_time);
        break;
    case 's':
        tab_voit[0].new_freiner(frame_time);
        break;
    default:
        break;
    }
    cout<<tab_voit[0].getAcceleration()<<endl;
    tab_voit[0].new_ralentir(frame_time);
    tab_voit[0].calculPosition(frame_time);

    for (int i=0; i<terrain.getNbProps(); i++)
    {   //on vérifie si la voiture est en collision avec un prop
        if (testColPropVoit(terrain.getProp(i), tab_voit[0]))
        {   //si oui, on met à jour la position de la voiture
            collisionPropVoit(terrain.getProp(i), tab_voit[0]);
        }
    }
    return 3;
}

void Jeu::update(ActionClavier const & Action)
{    tab_voit[0].action=Action;

    tab_voit[0].update(frame_time);

    for (int i=0; i<terrain.getNbProps(); i++)
    {   if (testColPropVoit(terrain.getProp(i), tab_voit[0]))
        {   collisionPropVoit(terrain.getProp(i), tab_voit[0]);
        }
    }
}   
