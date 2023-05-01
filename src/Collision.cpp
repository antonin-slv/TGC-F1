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

void collisionPropVoit(Props const & prop, Voiture & voit)
{   Vecteur diff = prop.getPos() - voit.getPos();
    voit.crash(diff, prop.getRotation());
}
