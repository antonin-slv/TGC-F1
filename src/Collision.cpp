#include "Collision.h"
#include "Voiture/Voiture.h"
#include "Terrain.h"
#include "Voiture/Physique.h"
#include "Voiture/Vecteur.h"

bool test_point_in_box(float x, float y, float l, float L)
{   return  (x >= - L && x <= L && y >= - l && y<= l);
}
bool test_point_in_box(Vecteur point, Vecteur box)
{   return test_point_in_box(point.x, point.y, box.x, box.y);
}

bool testColPropVoit(Props & prop, Voiture & voit)
{   Vecteur diff;
    diff = voit.getPos() - prop.getPos();

    diff.tourner(prop.getRotation());

    float nrot = prop.getRotation() + voit.getAngle();

    Vecteur car(voit.getLongueur(), voit.getLargeur());

    Vecteur avant(cos(nrot)*car.x,sin(nrot)*car.x);
    Vecteur cote (cos(nrot)*car.y,sin(nrot)*car.y);

    if (test_point_in_box(diff+avant, prop.getHitbox())) return true;
    if (test_point_in_box(diff+avant+cote, prop.getHitbox())) return true;
    if (test_point_in_box(diff+avant-cote, prop.getHitbox())) return true;

    if (test_point_in_box(diff-cote, prop.getHitbox())) return true;
    if (test_point_in_box(diff+cote, prop.getHitbox())) return true;

    if (test_point_in_box(diff-avant+cote, prop.getHitbox())) return true;
    if (test_point_in_box(diff-avant-cote, prop.getHitbox())) return true;
    if (test_point_in_box(diff-avant, prop.getHitbox())) return true;

    return false;
}

bool testColPropVoit2(Props & prop, Voiture & voit)
{   float rx = - voit.getX()+prop.getX();
    float ry = -voit.getY()+prop.getY();

    //on fait tourner le centre de la voiture autour de celui du prop
    rotation_xy(rx, ry, prop.getRotation());

    //somme de la rotation de la voiture et de la rotation du prop
    float nrot = prop.getRotation() + voit.getAngle();
    
    
    float lo_voit = voit.getLongueur();
    float La_voit = voit.getLargeur();
    //on fait tourner le point de la voiture à l'avant pour le ramener au bon endroit
    float lgx = cos(nrot)*lo_voit;
    float lgy = sin(nrot)*lo_voit;
    //pareil avec celui à droite
    float Lrx = cos(nrot)*La_voit;
    float Lry = sin(nrot)*La_voit;

    //mieux de dabord récupérer Larg et Long dans 2 variables ?

    //test si le point au bout de la voiture est dedans
    if (test_point_in_box(rx+lgx, ry+lgy, prop.getLong(), prop.getLarg())) return true;
    //test si le point à l'arrière de la voiture est dedans
    if (test_point_in_box(rx-lgx, ry-lgy, prop.getLong(), prop.getLarg())) return true;
    //test si le point à droite de la voiture est dedans
    if (test_point_in_box(rx+Lrx, ry+Lry, prop.getLong(), prop.getLarg())) return true;
    //test si le point à gauche de la voiture est dedans
    if (test_point_in_box(rx-Lrx, ry-Lry, prop.getLong(), prop.getLarg())) return true;

    //test si le coin avant droit de la voiture est dedans
    if (test_point_in_box(rx+lgx+Lrx, ry+lgy+Lry, prop.getLong(), prop.getLarg())) return true;
    //test si le coin avant gauche de la voiture est dedans
    if (test_point_in_box(rx+lgx-Lrx, ry+lgy-Lry, prop.getLong(), prop.getLarg())) return true;
    //test si le coin arrière droit de la voiture est dedans
    if (test_point_in_box(rx-lgx+Lrx, ry-lgy+Lry, prop.getLong(), prop.getLarg())) return true;
    //test si le coin arrière gauche de la voiture est dedans
    if (test_point_in_box(rx-lgx-Lrx, ry-lgy-Lry, prop.getLong(), prop.getLarg())) return true;

    return false;
}
