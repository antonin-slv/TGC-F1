#ifndef _INTERFACE_
#define _INTERFACE_

#include "Jeu.h"
#include "Terrain.h"
#include "Voiture/Voiture.h"

struct Editeur;

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include <vector>
#include <iostream>

using namespace std;
using namespace sf;

/** \brief Fonction qui affiche le texte text
 * \param window Fenêtre de rendu
 * \param text Texte (objet SFML) à afficher
 * \param charac_size Taille des caractères du texte
 * \param _x Position en x du texte par rapport à la fenêtre (en pixels)
 * \param _y Position en y du texte par rapport à la fenêtre (en pixels)
*/
void afficherDebug(RenderWindow & window, Text & text, int charac_size, float _x, float _y);


/** \brief Classe Interface
 *  Cette classe permet de charger les textures et de les afficher.
 *  Elle permet aussi de charger les props et les voitures.
 *  Elle permet aussi de charger les props de référence (pour l'éditeur)
*/
class Interface
{   private :
    vector<Sprite> props;//charger depuis un terrain
    vector<Sprite> ref_props;//chargés quand on ouvre un editeur
    
    /** \brief texture des checkpoints */
    Texture checkpoint;
    /** \brief texture de la ligne d'arrivée */
    Texture finish;
    /** \brief texture de l'herbe */
    Texture grass;
    /** \brief texture de la route avec vibreur */
    Texture road_kerb_a;
    /** \brief texture de la route avec vibreur 2*/
    Texture road_kerb_m;
    /** \brief texture de la route avec vibreur 3*/
    Texture road_kerb_z;

    /** \brief texture de la route */
    Texture road;
    /** \brief texture du virage de 12 mètres */
    Texture turn1;
    /** \brief texture du virage de 18 mètres */
    Texture turn2;
    /** \brief texture du virage de 24 mètres */
    Texture turn3;
    /** \brief texture du virage de 30 mètres */
    Texture turn4;

    /** \brief texture de la voiture */
    Texture text_voiture;
    /** \brief texture de l'ombre de la voiture */
    Texture text_voiture_ombre;
    /** \brief Sprite de l'ombre de la voiture*/
    Sprite voiture_ombre;
    public :
    /** \brief Sprite de la voiture */
    Sprite voiture;
    /** \brief Vue avec laquelle sont "draw" les éléments de l'interafce qui dépendent de la vue*/
    View vue;
    

    /** \brief Constructeur par défaut
     * Charge les textures depuis le dossier textures. immuable.
    */
    Interface();
    /** \brief Destructeur par défaut 
     * explicite la destruction des vectors
     * permet de savoir que le destructeur de la classe est appelé
    */
    ~Interface();

    /** \brief supprime le ième prop du vector props
     * \param i indice du prop à supprimer. le dernier par défaut ou si i = -1
    */
    void supprimerProp(int i=-1);
    /** \brief supprime tous les sprites du vector props
     * les textures sont conservées
    */
    void clearProps();
    /** \brief supprime le sprite de la voiture
     * neutralisé pour l'instant
     */
    void clearVoitures();

    /** \brief Charge le sprite associé au prop dans le vector props
     * \param prop Prop à charger
    */
    void loadProp(Props const & prop);
    /** \brief Charge l'ensemble des props du terrain dans le vector props
     * \param terrain Terrain à charger
     * \param texture_path Chemin inutilisé 
    */
    void loadTerrain(Terrain & terrain,string texture_path);
    /** \brief Charge la voiture dans le sprite voiture, et redéfini sa hitbox en accord avec la texture
     * l'ombre de la voiture est aussi chargée
     * \param voiture_ Voiture à charger
     * \param texture_path Chemin inutilisé
    */
    void loadVoiture(Voiture & voiture_, string texture_path);
    /** \brief Charge les props de référence dans le vector ref_props
     * Charge simplement un sprite pour chaque prop de référence si la texture existe
    */
    void loadRefProps();

    /** \brief affiche l'ensemble des props du vector props 
     * \param window Fenêtre de rendu
    */
    void drawTerrain(RenderWindow & window);

    /** \brief affiche la voiture et son ombre
     * \param window Fenêtre de rendu
     * \param voiture_ Voiture à afficher
    */
    void drawVoiture(RenderWindow & window,Voiture & voiture_);
    /** \brief affiche la hitbox de la voiture
     * \param window Fenêtre de rendu
     * \param voiture_ Voiture dont la hitbox est à afficher
    */
    void drawVoitureHitbox(RenderWindow & window,Voiture & voiture_);

    /** \brief retourne un lien vers la texture associée au Tip t
     * \param t Tip dont on veut la texture 
    */
    Texture * getTexture(Tip t);
    /** \brief affiche les props de référence sur la gauche de la fenêtre
     * \param window Fenêtre de rendu
    */
    void drawRefProps(RenderWindow & window);

    /** \brief retourne le Tip du prop sélectionné par le joueur (parmis les props de référence)
     * \param window Fenêtre de rendu
    */
    Tip refPropSelected(RenderWindow const & window);
    /** \brief retourne le dernier prop du vector props
     * \return LE prop lui même (pas de copie)
    */
    Sprite & dernierProp();
    /** \brief retourne le ième prop du vector props
     * \param i indice du prop à  si <0, boucle vers la fin du vector
     * \return LE prop lui même (pas de copie)
    */
    Sprite & getProp(int i);
};

#endif