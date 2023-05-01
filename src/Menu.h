#ifndef _Menu_H_
#define _Menu_H_

#include <iostream>
#include"Interface.h"

using namespace std;


/** \brief Structure contenant les paramètres du jeu
 *  
*/
struct Selection
{
    /**  \brief nom du circuit a charger */
    string nom_circuit;
    /**  \brief chemin vers le circuit a charger */
    string chemin_circuit;
    /**  \brief nombre de tours a faire */
    int nb_tours;
    /** \brief indice du circuit dans la liste des circuits */
    unsigned int indice_circuit;
    /** \brief volume de la musique */
    int volume;
    /** \brief decalaga de  la caméra dans le jeu */
    float decalage;
    /** \brief choix général (Jouer, editeur, quitter...) */
    string choix;
};

/** \brief Charge les paramètres du jeu
 * utilise le nom du circuit pour le trouver (à poser dans parametre_jeu.nom_circuit)
 * \param parametre_jeu paramètres du jeu qui seront modifiés
*/
bool get_parametre_circuit(Selection & parametre_jeu);

/**  \brief menu de sauvegarde d'un temps en console
 *  \param param paramètres du circuit dans lequel charger le temps
 * \param temps temps à sauvegarder */
bool sauvegarderTemp(Selection const & param, float temps);

void initBoutonCentre(RenderWindow & window, RectangleShape & rectangle, int y, int largeur, int hauteur);
void initBoutonGauche(RenderWindow & window, RectangleShape & rectangle, int y, int largeur, int hauteur);
void initCurseur(RenderWindow & window, RectangleShape & rectangle, int y, int largeur, int hauteur);
void initTexteCentre(RenderWindow & window, Text & texte, Font & font, int taille, string txt, int y);
void initTexteGauche(RenderWindow & window, Text & texte, Font & font, int taille, string txt, int y);
void initTitre(RenderWindow & window, Text & texte, Font & font, int taille, string txt, int y);

bool estSelectionne(RenderWindow & window, RectangleShape & rectangle);
void colorerSelectione(RenderWindow & window, RectangleShape & rectangle);
void colorerNonSelectione(RenderWindow & window, RectangleShape & rectangle);

void boucleMenu(RenderWindow & window, Selection & parametre_jeu);



#endif