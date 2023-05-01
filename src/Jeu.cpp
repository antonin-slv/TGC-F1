#include "Jeu.h"
#include <string>
#include "Collision.h"
#include "Voiture/Vecteur.h"

using namespace std;


Jeu::Jeu()
{   
    terrain=Terrain(100,30);
    nb_voit = 0;
    frame_time = 0.0167;
}

Jeu::Jeu(string path) {
    ChargerTerrain(path);
}

void Jeu::setframe_time(float const & tps) { frame_time = tps; }


void Jeu::ChargerTerrain(string path, int nb_tours) {
    terrain.chargerJSON(path);
    nb_tour = 0;
    num_checkpoint = -1;
    nb_tour_max = nb_tours;
    Props const & Ligne = terrain.getLigneArrivee();
    for (auto & V : tab_voit) {
        V.restart(Ligne.getPos(),Ligne.getRotation()+M_PI/2);
    }
}

Jeu::~Jeu() { 
    cout<<"debut destruction jeu"<<endl;
    tab_voit.clear();
    cout<<"fin destruction jeu"<<endl;
}

Terrain const & Jeu::getTerrain() { return terrain; }


void Jeu::ajouterVoiture(Voiture const & V)
{   //on créé une voiture identique à V et on l'ajoute au tableau
    tab_voit.push_back(Voiture(V));
    nb_voit++;
}

void Jeu::restart()
{   Voiture & voit = tab_voit[0];
    Props const & Ligne = terrain.getLigneArrivee();

    voit.restart(Ligne.getPos(), Ligne.getRotation()+M_PI/2);
    nb_tour = 0;
    num_checkpoint = -1;
}

Voiture & Jeu::getVoiture(int i) { return tab_voit[i]; }

int Jeu::update(ActionClavier const & Action)
{   Voiture & Voit = tab_voit[0];
    Voit.action=Action;
    bool on_road = false;
    bool on_grass = false;
    //gestion des collisions avec les props
    bool arrivee = (Voit.getCheckpoint()==(int)terrain.getOrdreCheckpoint().size());

    int code_sortie = 0;
    for (int i=0; i<terrain.getNbProps(); i++)
    {   Props const & prop = terrain.getProp(i);
        
        switch(prop.getType())
        {   case Tip::checkpoint :
                break;
            case Tip::finish :
                 if (arrivee && testColPropVoit(prop, Voit))
                 {  Voit.passer_checkpoint(true);
                    nb_tour++;
                    if (nb_tour == nb_tour_max)
                    {   cout<<"GAGNE"<<endl;
                        code_sortie = 1;
                    }
                    else {
                        cout<<"nouveau tour"<<endl;
                        code_sortie = -1;
                    }
                    on_road = true;
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
    if (!arrivee) {
        num_checkpoint = Voit.getCheckpoint();
        if (testColPropVoit(terrain.getProp(terrain.getOrdreCheckpoint()[num_checkpoint]), Voit)) {
            Voit.passer_checkpoint();
            num_checkpoint = Voit.getCheckpoint();
            cout<<"checkpoint "<<num_checkpoint<<endl;
        }
    }

    //si la voiture n'est pas sur la route/a une roue sur l'herbe, on la ralenti
    if (!on_road||on_grass) Voit.on_grass(frame_time);

    Voit.update(frame_time);
    return code_sortie;
}
