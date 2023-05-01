#ifndef _AFFICHAGESFML_H_
#define _AFFICHAGESFML_H_

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include "Editeur.h"
#include "Jeu.h"
#include "Menu.h"
#include "Terrain.h"
#include "Voiture/Voiture.h"
#include "Voiture/Vecteur.h"
#include "Interface.h"
#include <vector>
#include <iostream>

using namespace std;
using namespace sf;
/** \brief classe Gestion SFML, héritée de jeu
 * 
 *  
 * 
*/
class GestionSFML : public Jeu
{   private :
        
        float decalage;

        Interface interface;
        
        /** \brief temporisation du début du jeu (laisse le temps à l'utilisateur de comprendre) 
         *  \param window Fenêtre de rendu
         * \return true si le jeu doit continuer, false si l'utilisateur a appuyé sur echap ou a pour fermer
        */
        bool demarageJeuSFML(RenderWindow & window);//!appeller dans la boucle de jeu
    public :
        /** \brief Constructeur par défaut, ne fait rien */
        GestionSFML();

        /** \brief Destructeur par défaut
         * purment figuratif : montre que le destructeur est appelé
        */
        ~GestionSFML();

        /** \brief charge un nouveau niveau
         * \param path chemin du fichier json contenant la liste des props
         * \param nb_tours nombre de tours à faire pour gagner
        */
        void chargerNiveau(string path, int nb_tours=3);

        
        /** \brief boucle principale du jeu en SFML 
         *  \param window Fenêtre de rendu
         * \param temps_au_tour clock qui permet de savoir combien de temps s'est écoulé depuis le dernier tour
         *  \param decalage point auquel la caméra est décalée par apport à la voiture
        */
        Time boucleJeuSFML(RenderWindow & window, Clock & temps_au_tour, float decalage=0);
        /** \brief affiche le jeu avec SFML
         * demande à l'interface d'afficher les éléments (Terrain et voiture)
         * \param window Fenêtre de rendu
        */
        void afficherJeuSFML(RenderWindow & window);

        /** \brief test certaines fonctions de la classe 
         * \return true si les tests sont réussis, false sinon 
        */
        bool test_regression();

};

/** \brief passe l'action à effectuer en fonction de l'évènement clavier
 * \param event évènement clavier
 * \param action action à effectuer
*/
void getActionClavier(Event event, ActionClavier & action);

#endif