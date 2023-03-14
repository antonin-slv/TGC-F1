#include "Jeu.h"

Jeu::Jeu()
{   
    terrain=Terrain();
    nb_voit = 1;
    tab_voit = vector<Voiture>(nb_voit);
    frame_time = 1/60;
}


//ajouter dans le stockage un paramétrage de la voiture
Jeu::Jeu(string const & nom_fichier)
{   
    ChargerTerrain(nom_fichier);
    nb_voit = 1;
    tab_voit = vector<Voiture>(nb_voit);
    frame_time = 1/60;
    
}

Jeu::~Jeu()
{
    tab_voit.clear();
}

void Jeu::ChargerTerrain(string const & nom_fichier)
{
    terrain.chargerJSON(nom_fichier);
}

Terrain & Jeu::getTerrain()
{
    return terrain;
}

void Jeu::AjouterVoiture(Voiture const & V)
{   //on créé une voiture identique à V et on l'ajoute au tableau
    tab_voit.push_back(Voiture(V));
    nb_voit++;
}

Voiture & Jeu::getVoiture(int i)
{
    return tab_voit[i];
}


void Jeu::update(char const & touche)
{   //on met à jour la position de la voiture
    //tab_voit[0].update(frame_time, touche);
}