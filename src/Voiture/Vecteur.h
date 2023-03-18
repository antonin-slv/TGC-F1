#ifndef _VECTEUR_H_
#define _VECTEUR_H_


#include <math.h>



class Vecteur
{   public :
        float x;
        float y;
        

        Vecteur();
        Vecteur(float px, float py);
        Vecteur &operator=(const Vecteur & v);

        void setVecteur(float norme, float rotation);
        float getNorme() const;
        float getNorme2() const;
        float getRotation() const;
        void tourner(float angle=0);//sens horaire !!!!
};
       

        

Vecteur operator+(Vecteur a, Vecteur b);
Vecteur operator-(Vecteur a, Vecteur b);
Vecteur operator*(Vecteur a, float b);





#endif