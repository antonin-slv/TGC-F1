#include "Collision.h"
#include "Voiture/Voiture.h"
#include "Terrain.h"
#include "Voiture/Physique.h"
#include "Voiture/Vecteur.h"

bool test_point_in_box(float x, float y, float l, float L)
{   return  (x >= - l && x <= l && y >= - L && y<= L);
}
bool test_point_in_box(Vecteur point, Vecteur box)
{   return (point.x >= - box.x && point.x <= box.x && point.y >= - box.y && point.y <= box.y);
}

bool test_colPointbox(Vecteur point, Vecteur const &  box, float Rotation)
{   point = point;
    point.tourner(-Rotation);
    return test_point_in_box(point,box);
}

bool testColPropVoit(Props const & prop, Voiture & voit)
{   Vecteur diff;
    diff = voit.getPos() - prop.getPos();

    diff.tourner(prop.getRotation());

    float nrot = prop.getRotation() + voit.getAngle();

    
    Vecteur avant(cos(nrot)*voit.getHitbox().x,sin(nrot)*voit.getHitbox().x);
    Vecteur cote (cos(nrot)*voit.getHitbox().y,sin(nrot)*voit.getHitbox().y);

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

bool testColPropVoit2(Props const & prop, Voiture & voit)
{   Vecteur diff= voit.getPos() - prop.getPos();
    
    //on fait tourner le centre de la voiture autour de celui du prop
    diff.tourner(prop.getRotation());

    //somme de la rotation de la voiture et de la rotation du prop
    float nrot = prop.getRotation() + voit.getAngle();
    
    Vecteur hitbox_voit = voit.getHitbox();

    float crot = cos(nrot);
    float srot = sin(nrot);
    //on fait tourner le point de la voiture à l'avant pour le ramener au bon endroit
    float lgx = crot*hitbox_voit.x;
    float lgy = srot*hitbox_voit.x;
    //pareil avec celui à droite
    float rx = crot*hitbox_voit.y;
    float ry = srot*hitbox_voit.y;

    //mieux de dabord récupérer Larg et Long dans 2 variables ?

    //test si le point au bout de la voiture est dedans
    if (test_point_in_box(diff.x+lgx, diff.y+lgy, prop.getLong(), prop.getLarg())) return true;
    //test si le point à l'arrière de la voiture est dedans
    if (test_point_in_box(diff.x-lgx, diff.y-lgy, prop.getLong(), prop.getLarg())) return true;
    //test si le point à droite de la voiture est dedans
    if (test_point_in_box(diff.x+rx, diff.y+ry, prop.getLong(), prop.getLarg())) return true;
    //test si le point à gauche de la voiture est dedans
    if (test_point_in_box(diff.x-rx, diff.y-ry, prop.getLong(), prop.getLarg())) return true;

    //test si le coin avant droit de la voiture est dedans
    if (test_point_in_box(diff.x+lgx+rx, diff.y+lgy+ry, prop.getLong(), prop.getLarg())) return true;
    //test si le coin avant gauche de la voiture est dedans
    if (test_point_in_box(diff.x+lgx-rx, diff.y+lgy-ry, prop.getLong(), prop.getLarg())) return true;
    //test si le coin arrière droit de la voiture est dedans
    if (test_point_in_box(diff.x-lgx+rx, diff.y-lgy+ry, prop.getLong(), prop.getLarg())) return true;
    //test si le coin arrière gauche de la voiture est dedans
    if (test_point_in_box(diff.x-lgx-rx, diff.y-lgy-ry, prop.getLong(), prop.getLarg())) return true;

    return false;
}


void collisionPropVoit(Props const & prop, Voiture & voit)
{   Vecteur diff = prop.getPos() - voit.getPos();
    voit.crash(diff, prop.getRotation());
}
