#include "Affichage.h"

void afficherPropsTxt(Props const * p)
{   cout << "PROPS " << p->getType() <<" : "<<endl;
    cout << "(" << p->getX() << ',' << p->getY() << ") avec " << p->getRotation()*180/M_PI << "°" << endl;
    cout << "L = " << p->getLarg() << " et l = " << p->getLong() << endl;
}

void afficherTerrainGenTxt(Terrain & terrain)
{
    cout << "Terrain de " << terrain.getLargeur() <<"m, par" << terrain.getLongueur() << " m"<<endl;
    cout << "Nombre de props : " << terrain.getNbProps() << endl;
}

void afficherTerrainTxt(Terrain & terrain)
{
    afficherTerrainGenTxt(terrain);

    for (int i = 0; i < terrain.getNbProps(); i++)
    {
        cout << i << " : ";
        afficherPropsTxt(terrain.getProp(i));
        
    }
}


void afficherVoitureTxt(Voiture & voit)
{
    cout<<"("<<voit.getX()<<','<<voit.getY()<<") at ";
    cout<<voit.getVitesse()*3.6 << " km/h ";
    cout<<" with : "<<voit.getAngle()*180/M_PI<<"°"<<endl;

}
