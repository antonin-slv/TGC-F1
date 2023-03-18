#include <iostream>
#include <fstream>
#include <chrono>
#include <thread>

#include "Voiture/Physique.h"
#include "Voiture/Voiture.h"
#include "Terrain.h"
#include "Jeu.h"
#include "Affichage.h"
#include "Collision.h"

#include "json.hpp"
#include "winTxt.h"

using namespace std::this_thread; // sleep_for, sleep_until
using namespace std::chrono; // milliseconds, system_clock, seconds
using json = nlohmann::json; //pour le json
using namespace std;

int main(){

  Jeu J1;
  J1.ChargerTerrain("data/circuits/test.json");

  cout<<"voiture du jeu : ";
  afficherVoitureTxt(J1.getVoiture(0));
  cout<<"Terrain du jeu :"<<endl;
  afficherTerrainTxt(J1.getTerrain());
  cout << "init ok" << endl;

  bool fin = false;
  float i = 0;
  J1.setframe_time(0.008);
  //sleep_for(milliseconds(2000));
  termClear();
  WinTXT win(J1.getTerrain().getLongueur()*1.5,J1.getTerrain().getLargeur()*1.5);
 
  while (!fin){
    
    time_point<system_clock> start, end;
    start = system_clock::now();

    i+=0.0167;

    fin = J1.update('z');

    if (true)
    {
      win.clear(' ');
    
      for (int x = 0; x < J1.getTerrain().getLongueur()*1.5; x++)
      { for (int y = 0; y < J1.getTerrain().getLargeur()*1.5; y++)
        { for (int i = 0; i < J1.getTerrain().getNbProps(); i++)
          { if (test_point_in_box(Vecteur(x,y)-J1.getTerrain().getProp(i).getPos(),J1.getTerrain().getProp(i).getHitbox()))
            { win.print(x,y,'P'); }   
          }
          if (test_point_in_box(Vecteur(x,y)-J1.getVoiture(0).getPos(),J1.getVoiture(0).getHitbox()))
          { win.print(x,y,'V'); }
        }
      }
      win.draw();
    
    }

    //termMove(J1.getTerrain().getLongueur(),J1.getTerrain().getLargeur());
      cout << i << "s" << endl
           << "vitesse : " << J1.getVoiture(0).getVitesse()*3.6 << "km/h " << endl
           << "position : " << J1.getVoiture(0).getX() << " " << J1.getVoiture(0).getY() << endl;
    
    end = system_clock::now();
    duration<double> elapsed_seconds = end-start;
    sleep_for(milliseconds(8) - duration_cast<milliseconds>(elapsed_seconds));
  }
  termClear();
  cout << "Vous avez tapé un mur à " << J1.getVoiture(0).getVitesse()*3.6 << "km/h ! J'espère que vous aviez bien attaché la ceinture de sécurité !" << endl;
  return 0;
}