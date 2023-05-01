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

/**
 * @brief Genere un rectangle pour servir de corps a un bouton
 * 
 * @param window fenetre de rendu
 * @param rectangle rectangle a positionner
 * @param y position en y
 * @param largeur largeur du rectangle
 * @param hauteur hauteur du rectangle
 */

void initBoutonCentre(RenderWindow & window, RectangleShape & rectangle, int y, int largeur, int hauteur);

/**
 * @brief Genere un rectangle pour servir de curseur
 * 
 * @param window fenetre de rendu
 * @param rectangle rectangle a positionner
 * @param y position en y
 * @param largeur largeur du rectangle
 * @param hauteur hauteur du rectangle
 */
void initCurseur(RenderWindow & window, RectangleShape & rectangle, int y, int largeur, int hauteur);

/**
 * @brief Genere un texte pour servir de texte de bouton
 * 
 * @param window fenetre de rendu
 * @param texte texte a positionner
 * @param font police d'ecriture
 * @param taille taille du texte
 * @param txt texte a afficher
 * @param y position en y
 */
void initTexteCentre(RenderWindow & window, Text & texte, Font & font, int taille, string txt, int y);

/**
 * @brief Genere un texte pour servir de titre
 * 
 * @param window fenetre de rendu
 * @param texte texte a positionner
 * @param font police d'ecriture
 * @param taille taille du texte
 * @param txt texte a afficher
 * @param y position en y
 */
void initTitre(RenderWindow & window, Text & texte, Font & font, int taille, string txt, int y);

/**
 * @brief Renvoie si le rectangle est selectionne
 * 
 * @param window fenetre de rendu
 * @param rectangle rectangle a tester
 * @return bool
 */
bool estSelectionne(RenderWindow & window, RectangleShape & rectangle);

/**
 * @brief Colore le bouton si il est selectionne
 * 
 * @param window fenetre de rendu
 * @param rectangle rectangle a colorer
 */
void colorerSelectione(RenderWindow & window, RectangleShape & rectangle);

/**
 * @brief Colorer le bouton si il n'est pas selectionne
 * 
 * @param window fenetre de rendu
 * @param rectangle rectangle a colorer
 */
void colorerNonSelectione(RenderWindow & window, RectangleShape & rectangle);

/**
 * @brief Effectue la boucle du menu principal
 * 
 * @param window fenetre de rendu
 * @param parametre_jeu parametres du jeu
 */
void boucleMenu(RenderWindow & window, Selection & parametre_jeu);

#endif