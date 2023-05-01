#ifndef _Editeur_H_
#define _Editeur_H_

#include "Terrain.h"
#include "Interface.h"
#include "Menu.h"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>


#include <vector>
#include <iostream>
#include <fstream>

using namespace std;
using namespace sf;



/** \brief fonction permettant de préparer le fichier liste_niveau.json !!!interface dans la console!!! 
 * Cette fonction update le fichier liste_niveau.json si l'utilisateur valide
 * et donne un lien pour pouvoir sauvegarder le niveau
 * \param path chemin dans lequel le niveau sera sauvegardé si il est validé
 * \return true si if faut effectuer la sauvegarde, false sinon 
*/
bool Sauvegarder_Niveau_txtGlobal(string & path);

/** \brief fonction permettant de sélectionner un niveau !!!interface dans la console!!! 
 *  \param path chemin du fichier circuit à charger
 * \return true si on charge un niveau, false sinon (y compris si on en supprime un)
*/
bool Selection_niveau(string & path);


/**
 * \class Classe Editeur
 * \brief Classe d'édition de Terrain, fille de ce dernier
 *  Cette classe permet de créer un terrain et de le sauvegarder dans un fichier json, ainsi que de le charger, ou de le supprimer.
 */
class Editeur : public Terrain
{   
    private :
        /** \brief centre de la vue */
        Vector2f centre;
        /** \brief niveau de zoom*/
        float zoom;//10 par défaut
        /** \brief indice du prop sélectionné*/
        int prop_selectionne;
        

        //varibles pour la gestion des évènements
        /** \brief booléen qui indique si on est en train de déplacer la vue*/ 
        bool deplacer_vue = false;
        /** \brief booléen qui indique si on est en train d'ajouter un prop*/
        bool ajout_prop = false;
        /** \brief position de la souris à la frame précédente*/
        Vector2i mouse_prev_pos;

        /** \brief Interface de l'éditeur
         *  y sont stockés les textures et les différents éléments à afficher
        */
        Interface interface;
        
    public :
        /** \brief Constructeur par défaut*/
        Editeur();
        /** \brief Lie les éléments de l'Editeur à l'affichage
         * utilise window.draw(). pas de window.display()
         * \param window Fenêtre de rendu
        */
        void lier_window(RenderWindow & window);
        /** \brief zoom sur le terrain \param z Facteur de zoom */
        void zoom_(float z);
        /** \brief Déplace la caméra \param dx Déplacement en x \param dy Déplacement en y */
        void deplacer(float dx=0, float dy=0);

        /** \brief Boucle principale de l'éditeur \param window Fenêtre de rendu \param volume Volume de la musique */
        void boucleEditeur(RenderWindow & window, int volume);
        

        /** \brief Ajoute un prop au terrain
         * \param t Type du prop
         * \param pos Position du prop 
        */
        void ajouter_prop(Tip t = Tip::road, Vector2f pos = Vector2f(0,0));
        /** \brief Sélectionne un prop nouveau prop, et centre la caméra dessus 
         * \param plus_recent Si true, sélectionne un plus récent, sinon un plus ancien */
        void select_prop(bool plus_recent = true);
        /** \brief Supprime un prop 
         * \param i Indice du prop à supprimer. si i=-1, supprime le prop sélectionné */
        void supprimer_prop(int i=-1);
        /** \brief Déplace le prop sélectionné 
         * \param dx Déplacement en x 
         * \param dy Déplacement en y */
        void deplacer_prop(float dx, float dy);
        /** \brief Tourne le prop sélectionné de angle dans le sens horaire
         * \param angle Angle de rotation */
        void rotate_prop(float angle=90);

        /** \brief Initialise les propriétés des props */
        void Init_props();

        /** \brief Sauvegarde le terrain dans un fichier json \param path Chemin du fichier */
        void sauvegarder(string path);
        /** \brief Charge un nouveau terrain depuis un fichier json si il existe \param path Chemin du fichier */
        bool charger(string path = "data/circuits/test1.json");

        /** \brief Initialise les propriétés des props de référence
         * ce sont les props à gauche de l'écran
        */
        void Init_ref_props();

        /** \brief Gère les évènements clavier et leurs conséquences de l'éditeur \param window Fenêtre de rendu \return true si on doit quitter l'éditeur */
        bool gestionEvent(RenderWindow & window);
        /** \brief Gère les évènements de la souris \param window Fenêtre de rendu */
        void gestionSouris(RenderWindow const & window);

        /** \brief Teste les fonctions de l'éditeur \return true si les tests sont réussis */
        bool test_regression();
};

/** \brief Convertit une position normale en position sur la grille
* \param pos Position à convertir */
void map_pos_to_grid(Vecteur & pos);

#endif