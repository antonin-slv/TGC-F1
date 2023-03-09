#include "Jeu.h"

Jeu::Jeu()
{   
    terrain = new Terrain(1000, 1000, 100);
    nb_voit = 1;
    tab_voit = vector<Voiture>(nb_voit);
}

Jeu::~Jeu()
{
    if(terrain != nullptr) delete terrain;
    tab_voit.clear();
}

void Jeu::ChargerTerrain(string const & nom_fichier)
{
    terrain->chargerJSON(nom_fichier);
}

Terrain * Jeu::getTerrain() const
{
    return  terrain;
}

void Jeu::AjouterVoiture(Voiture & V)
{
    tab_voit.push_back(Voiture(V));
    nb_voit++;
}

Voiture & Jeu::getVoiture(int i)
{
    return tab_voit[i];
}