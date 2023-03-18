#include "Vecteur.h"


Vecteur::Vecteur()
{
    x = 0;
    y = 0;
}

Vecteur::Vecteur(float px, float py)
{
    x = px;
    y = py;
}

Vecteur &Vecteur::operator=(const Vecteur & v)
{
    x = v.x;
    y = v.y;
    return *this;
}
void Vecteur::setVecteur(float norme, float rotation)
{
    x = norme * cos(rotation);
    y = norme * sin(rotation);
}
float Vecteur::getNorme() const
{
    return sqrt(x*x + y*y);
}
float Vecteur::getNorme2() const
{
    return x*x + y*y;
}
float Vecteur::getRotation() const
{
    return atan2(y, x);
}

void Vecteur::tourner(float angle)
{   float x2 = x*cos(angle) - y*sin(angle);
    y = x*sin(angle) + y*cos(angle);
    x = x2;
}
Vecteur operator+(Vecteur a, Vecteur b)
{
    return Vecteur(a.x+b.x, a.y+b.y);
}

Vecteur operator-(Vecteur a, Vecteur b)
{
    return Vecteur(a.x-b.x, a.y-b.y);
}

Vecteur operator*(Vecteur a, float b)
{
    return Vecteur(a.x*b, a.y*b);
}

