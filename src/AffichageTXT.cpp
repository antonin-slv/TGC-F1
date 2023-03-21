#include "AffichageTXT.h"

void afficherPropsTxt(Props const & p)
{   cout << "PROPS " << p.getType() <<" : "<<endl;
    cout << "(" << p.getX() << ',' << p.getY() << ") avec " << p.getRotation()*180/M_PI << "°" << endl;
    cout << "L = " << p.getLarg() << " et l = " << p.getLong() << endl;
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

void afficherJeuFTXT(WinTXT & win,Jeu & J1,const int i, const int zoom)
{   win.clear('.');
    Vecteur temp;
    Voiture v;
    Props p;
    for (int x = 0; x < J1.getTerrain().getLongueur()+20; x++)
    {   for (int y = 0; y < J1.getTerrain().getLargeur()+20; y++)
        {   for (int i = 0; i < J1.getTerrain().getNbProps(); i++)
            { //cout<<"prop";
            p = J1.getTerrain().getProp(i);
            temp = (Vecteur(x,y)*(10/(float)zoom) - p.getPos());
            temp.tourner( -p.getRotation());
            if (test_point_in_box( temp, p.getHitbox() ))
            { win.print(x,y,'P'); }
            }

        v=J1.getVoiture(0);
        temp=(Vecteur(x,y)*(10/(float)zoom)-v.getPos());
        temp.tourner(-v.getAngle() );
        if (test_point_in_box(temp,v.getHitbox()))
        { win.print(x,y,'V'); }
        }
    }
    win.draw();
    //termMove(J1.getTerrain().getLongueur(),J1.getTerrain().getLargeur());
    cout << i << "s" << endl
        << "vitesse : " << J1.getVoiture(0).getVitesse()*3.6 << "km/h " << endl
        << "position : " << J1.getVoiture(0).getX() << " " << J1.getVoiture(0).getY() << endl;

    
}