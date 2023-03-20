#include <iostream>
#include <fstream>
#include <chrono>
#include <thread>

#include "Voiture/Physique.h"
#include "Voiture/Voiture.h"
#include "Voiture/Moteur.h"
#include "Voiture/Roues.h"
#include "Voiture/Vecteur.h"

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
  J1.setframe_time(0.016);
  //sleep_for(milliseconds(2000));
  termClear();
  WinTXT win(J1.getTerrain().getLongueur()+15,J1.getTerrain().getLargeur()+10);
  bool pause = false;
  while (!fin){
    
    time_point<system_clock> start, end;
    start = system_clock::now();


    char a = win.getCh();
    if (a == 'p')
    { cout<<"pause"<<endl;
      pause = !pause;
      if (!pause) a = win.getCh();
    } 
    if (a == 'q') fin = true;

    if (!pause)
    { i+=0.008;
      cout<<endl<<a<<endl;
      J1.update(a);
      win.clear('.');
      Vecteur temp;
      Voiture v;
      Props p;
      for (int x = 0; x < J1.getTerrain().getLongueur(); x++)
      { for (int y = 0; y < J1.getTerrain().getLargeur(); y++)
        { for (int i = 0; i < J1.getTerrain().getNbProps(); i++)
          { //cout<<"prop";
            p = J1.getTerrain().getProp(i);
            temp = Vecteur(x,y) - p.getPos();
            temp.tourner( p.getRotation());
            if (test_point_in_box( temp, p.getHitbox() ))
            { win.print(x,y,'P'); }
          }

          v=J1.getVoiture(0);
          temp=Vecteur(x,y)-v.getPos();
          temp.tourner(v.getAngle() );
          if (test_point_in_box(temp,v.getHitbox()))
          { win.print(x,y,'V'); }
        }
      }
    }
    win.draw();
      //termMove(J1.getTerrain().getLongueur(),J1.getTerrain().getLargeur());
        cout << i << "s  ,   touche pressée : " << a << endl
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