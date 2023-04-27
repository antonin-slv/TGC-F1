#ifndef _Menu_H_
#define _Menu_H_

#include <iostream>
#include"Interface.h"

using namespace std;

void initBoutonCentre(RenderWindow & window, RectangleShape & rectangle, int y, int largeur, int hauteur);
void initBoutonGauche(RenderWindow & window, RectangleShape & rectangle, int y, int largeur, int hauteur);
void initCurseur(RenderWindow & window, RectangleShape & rectangle, int y, int largeur, int hauteur);
void initTexteCentre(RenderWindow & window, Text & texte, Font & font, int taille, string txt, int y);
void initTexteGauche(RenderWindow & window, Text & texte, Font & font, int taille, string txt, int y);
void initTitre(RenderWindow & window, Text & texte, Font & font, int taille, string txt, int y);

bool estSelectionne(RenderWindow & window, RectangleShape & rectangle);
void colorerSelectione(RenderWindow & window, RectangleShape & rectangle);
void colorerNonSelectione(RenderWindow & window, RectangleShape & rectangle);

int boucleMenu(RenderWindow & window, int & volume, float & decalage);

#endif