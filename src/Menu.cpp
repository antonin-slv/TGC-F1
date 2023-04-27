#include "Menu.h"
#include <iostream>
#include <string>
#include <SFML/Audio.hpp>

using namespace std;
using namespace sf;

//DEFINITION DES FONCTIONS=========================================================================

/**
 * @brief Genere un rectangle au centre de l'ecran pour servir de corps au bouton
 * 
 * @param window La fenêtre de jeu
 * @param rectangle Le rectangle à initialiser
 * @param y La hauteur sur l'ecran
 * @param largeur Largeur du bouton
 * @param hauteur Hauteur du bouton
 */
void initBoutonCentre(RenderWindow & window, RectangleShape & rectangle, int y, int largeur, int hauteur){
    rectangle.setFillColor(Color::Transparent);
    rectangle.setOutlineThickness(3);
    rectangle.setOutlineColor(Color::White);
    rectangle.setSize(Vector2f(largeur,hauteur));
    rectangle.setPosition((window.getSize().x-largeur)/2, y);
}

/**
 * @brief Genere un rectangle sur la partie gauche de l'ecran pour servir de corps au bouton
 * 
 * @param window La fenêtre de jeu
 * @param rectangle Le rectangle à initialiser
 * @param y La hauteur sur l'ecran
 * @param largeur Largeur du bouton
 * @param hauteur Hauteur du bouton
 */
void initBoutonGauche(RenderWindow & window, RectangleShape & rectangle, int y, int largeur, int hauteur){
    initBoutonCentre(window, rectangle, y, largeur, hauteur);
    rectangle.setPosition((window.getSize().x*2/3-largeur)/2, y);
}

/**
 * @brief Genere un rectangle sur la partie droite de l'ecran pour servir de corps au bouton
 * 
 * @param window La fenêtre de jeu
 * @param rectangle Le rectangle à initialiser
 * @param y La hauteur sur l'ecran
 * @param largeur Largeur du bouton
 * @param hauteur Hauteur du bouton
 */
void initBoutonDroite(RenderWindow & window, RectangleShape & rectangle, int y, int largeur, int hauteur){
    initBoutonCentre(window, rectangle, y, largeur, hauteur);
    rectangle.setPosition((window.getSize().x*4/3-largeur)/2, y);
}

/**
 * @brief Genere un rectangle au centre de l'ecran pour servir de curseur
 * 
 * @param window La fenêtre de jeu
 * @param rectangle Le rectangle à initialiser
 * @param y La hauteur sur l'ecran
 * @param largeur Largeur du bouton
 * @param hauteur Hauteur du bouton
 */
void initCurseur(RenderWindow & window, RectangleShape & rectangle, int y, int largeur, int hauteur){
    initBoutonCentre(window, rectangle, y, largeur, hauteur);
    rectangle.setFillColor(Color::White);
}

/**
 * @brief Genere un texte au centre de l'ecran à la hauteur y
 * 
 * @param window La fenêtre de jeu
 * @param texte L'objet texte à initialiser
 * @param font La police à utiliser
 * @param taille la taille du texte 
 * @param txt Le texte à écrire
 * @param y la hauteur sur l'ecran
 */
void initTexteCentre(RenderWindow & window, Text & texte, Font & font, int taille, string txt, int y){
    texte.setFont(font);
    texte.setCharacterSize(taille);
    texte.setString(txt);
    texte.setFillColor(Color::White);
    texte.setPosition((window.getSize().x-texte.getLocalBounds().width)/2, y+15);
}

/**
 * @brief Genere un texte sur la partie gauche de l'ecran à la hauteur y
 * 
 * @param window La fenêtre de jeu
 * @param texte L'objet texte à initialiser
 * @param font La police à utiliser
 * @param taille la taille du texte 
 * @param txt Le texte à écrire
 * @param y La hauteur sur l'ecran
 */
void initTexteGauche(RenderWindow & window, Text & texte, Font & font, int taille, string txt, int y){
    initTexteCentre(window, texte, font, taille, txt, y);
    texte.setPosition((window.getSize().x*2/3 - texte.getGlobalBounds().width)/2, y+15);
}

void initTexteDroite(RenderWindow & window, Text & texte, Font & font, int taille, string txt, int y){
    initTexteCentre(window, texte, font, taille, txt, y);
    texte.setPosition((window.getSize().x*4/3 - texte.getGlobalBounds().width)/2, y+15);
}

/**
 * @brief Genere un titre
 * 
 * @param window La fenêtre de jeu
 * @param texte L'objet texte à initialiser
 * @param font La police à utiliser
 * @param taille la taille du texte 
 * @param txt Le texte à écrire
 * @param y La hauteur sur l'ecran
 */
void initTitre(RenderWindow & window, Text & texte, Font & font, int taille, string txt, int y){
    initTexteCentre(window, texte, font, taille, txt, y);
    texte.setFillColor(Color::Red);
}

/**
 * @brief Retourne si la souris est sur un bouton
 * 
 * @param window La fenêtre de jeu
 * @param texte L'objet texte à initialiser
 * @param font La police à utiliser
 * @param taille la taille du texte 
 * @param txt Le texte à écrire
 * @param y La hauteur sur l'ecran
 * @return bool Si la souris est sur le bouton
 */
bool estSelectionne(RenderWindow & window, RectangleShape & rectangle){
    return rectangle.getGlobalBounds().contains(Mouse::getPosition(window).x, Mouse::getPosition(window).y);
}

/**
 * @brief Colore le bouton en selectionné
 * 
 * @param rectangle Le rectangle à colorer
 */
void colorerSelectionne(RectangleShape & rectangle){
    rectangle.setFillColor(Color(32,32,32));
    rectangle.setOutlineColor(Color::Red);
}

/**
 * @brief Colore le bouton en non selectionné
 * 
 * @param rectangle Le rectangle à colorer
 */
void colorerNonSelectionne(RectangleShape & rectangle){
    rectangle.setFillColor(Color::Transparent);
    rectangle.setOutlineColor(Color::White);
}

/**
 * @brief Affiche le menu
 * 
 * @param window La fenêtre de jeu
 * @param volume Le volume de la musique
 * @param decalage Le decalage de la caméra
 * @return int Le choix du joueur
 */
int boucleMenu(RenderWindow & window, int & volume, float & decalage){

    //INITIALISATION===============================================================================

    window.setView(window.getDefaultView());

    bool parametre = false;
    bool choix_niveau = false;

    Music music;
    music.openFromFile("data/sounds/menu.wav");
    music.setVolume(volume);
    music.setLoop(true);
    music.play();

    //RECTANGLES===================================================================================

    RectangleShape boutonJouer;
    initBoutonCentre(window, boutonJouer, 450, 400, 100);

    RectangleShape boutonEditeur;
    initBoutonCentre(window, boutonEditeur, 600, 400, 100);

    RectangleShape boutonParametre;
    initBoutonCentre(window, boutonParametre, 750, 400, 100);

    RectangleShape boutonQuitter;
    initBoutonCentre(window, boutonQuitter, 900, 400, 100);

    RectangleShape barreVolume;
    initBoutonCentre(window, barreVolume, 300, 600, 10);

    RectangleShape barreVolume2;
    initCurseur(window, barreVolume2, 300, 600, 10);

    RectangleShape curseurVolume;
    initCurseur(window, curseurVolume, 300, 10, 30);

    RectangleShape barreDecalage;
    initBoutonCentre(window, barreDecalage, 500, 600, 10);

    RectangleShape barreDecalage2;
    initCurseur(window, barreDecalage2, 500, 600, 10);

    RectangleShape curseurDecalage;
    initCurseur(window, curseurDecalage, 500, 10, 30);

    RectangleShape boutonRetour;
    initBoutonCentre(window, boutonRetour, 900, 400, 100);

    vector<RectangleShape> boutonsNiveaux(5);
    for(int i=0; i<5; i++){
        initBoutonGauche(window, boutonsNiveaux[i], 150*(i+1), 300, 75);
    }

    RectangleShape boutonCharger;
    initBoutonDroite(window, boutonCharger, 450, 300, 75);

    //TEXTES=======================================================================================

    Font font;
    font.loadFromFile("data/fonts/F1.ttf");

    Text texteTitre;
    initTitre(window, texteTitre, font, 100, "The Great Competition :", 50);

    Text texteSousTitre;
    initTitre(window, texteSousTitre, font, 100, "Fast One", 175);

    Text texteJouer;
    initTexteCentre(window, texteJouer, font, 50, "Jouer", 450);

    Text texteEditeur;
    initTexteCentre(window, texteEditeur, font, 50, "Editeur", 600);

    Text texteParametre;
    initTexteCentre(window, texteParametre, font, 50, "Parametres", 750);

    Text texteQuitter;
    initTexteCentre(window, texteQuitter, font, 50, "Quitter", 900);

    Text texteCredits;
    initTexteCentre(window, texteCredits, font, 25, "version alpha", 0);
    texteCredits.setPosition(window.getSize().x*0.84, window.getSize().y*0.9); 

    Text texteCredits2;
    initTexteCentre(window, texteCredits2, font, 25, "by Ninotnas & Sipior", 0);
    texteCredits2.setPosition(window.getSize().x*0.84, window.getSize().y*0.95);

    Text texteVolume;
    initTexteCentre(window, texteVolume, font, 50, "Volume : " + to_string(volume), 200);

    Text texteDecalage;
    initTexteCentre(window, texteDecalage, font, 50, "Decalage : " + to_string(decalage), 600);

    Text texteConseil;
    initTexteCentre(window, texteConseil, font, 25, "Pour regler le volume, utilisez les fleches HAUT et BAS", 700);

    Text texteConseil2;
    initTexteCentre(window, texteConseil2, font, 25, "Pour regler le decalage, utilisez les fleches GAUCHE et DROITE", 750);

    Text texteRetour;
    initTexteCentre(window, texteRetour, font, 50, "Retour", 900);

    vector<Text> textesNiveaux(5);
    for(int i=0; i<5; i++){
        initTexteGauche(window, textesNiveaux[i], font, 35, "Niveau " + to_string(i+1), (i+1)*150);
    }

    Text texteCharger;
    initTexteDroite(window, texteCharger, font, 35, "Charger", 450);


    //BOUCLE PRINCIPALE============================================================================
    while (window.isOpen()){
        Event event;
        while (window.pollEvent(event)){
            if (event.type == Event::Closed){
                window.close();
            }
            if(!parametre and !choix_niveau){ //Menu principal ======================================================
                if (event.type == Event::MouseButtonPressed){
                    if (event.mouseButton.button == Mouse::Left){
                        if (estSelectionne(window, boutonJouer)){
                            choix_niveau = true;
                        }
                        if (estSelectionne(window, boutonEditeur)){
                            return 2;
                        }
                        if (estSelectionne(window, boutonParametre)){
                            parametre = true;
                        }
                        if (estSelectionne(window, boutonQuitter)){
                            return 3;
                        }
                    }
                }
                if(estSelectionne(window, boutonJouer)){
                    colorerSelectionne(boutonJouer);
                }
                else{
                    colorerNonSelectionne(boutonJouer);
                }

                if(estSelectionne(window, boutonEditeur)){
                    colorerSelectionne(boutonEditeur);
                }
                else{
                    colorerNonSelectionne(boutonEditeur);
                }
                
                if(estSelectionne(window, boutonParametre)){
                    colorerSelectionne(boutonParametre);
                }
                else{
                    colorerNonSelectionne(boutonParametre);
                }

                if(estSelectionne(window, boutonQuitter)){
                    colorerSelectionne(boutonQuitter);
                }
                else{
                    colorerNonSelectionne(boutonQuitter);
                }
            }
            if(choix_niveau){
                if (event.type == Event::MouseButtonPressed){
                    if (event.mouseButton.button == Mouse::Left){
                        for(int i=0; i<5; i++){
                            if (estSelectionne(window, boutonsNiveaux[i])){
                                return i+4;
                            }
                        }
                        if(estSelectionne(window, boutonRetour)){
                            choix_niveau = false;
                        }
                    }
                }
                for(int i=0; i<5; i++){
                    if(estSelectionne(window, boutonsNiveaux[i])){
                        colorerSelectionne(boutonsNiveaux[i]);
                    }
                    else{
                        colorerNonSelectionne(boutonsNiveaux[i]);
                    }
                }
                if(estSelectionne(window, boutonCharger)){
                    colorerSelectionne(boutonCharger);
                }
                else{
                    colorerNonSelectionne(boutonCharger);
                }
                if(estSelectionne(window, boutonRetour)){
                    colorerSelectionne(boutonRetour);
                }
                else{
                    colorerNonSelectionne(boutonRetour);
                }
            }
            if(parametre){ //Menu parametre ================================================================
                if(event.type == Event::KeyPressed){
                    if(event.key.code == Keyboard::Escape){
                        choix_niveau = false;
                        parametre = false;
                    }
                }
                if (event.type == Event::MouseButtonPressed){
                    if (event.mouseButton.button == Mouse::Left){
                        if (estSelectionne(window, boutonRetour)){
                            choix_niveau = false;
                            parametre = false;
                        }
                    }
                }
                if(estSelectionne(window, boutonRetour)){
                    colorerSelectionne(boutonRetour);
                }
                else{
                    colorerNonSelectionne(boutonRetour);
                }
                if(Keyboard::isKeyPressed(Keyboard::Up)){
                    if(volume < 96){
                        volume += 5;
                    }
                    else{
                        volume = 100;
                    }
                }
                if(Keyboard::isKeyPressed(Keyboard::Down)){
                    if(volume > 4){
                        volume -= 5;
                    }
                    else{
                        volume = 0;
                    }
                }
                if(Keyboard::isKeyPressed(Keyboard::Right)){
                    if(decalage < 4.5){
                        decalage += 0.5;
                    }
                    else{
                        decalage = 5;
                    }
                }
                if(Keyboard::isKeyPressed(Keyboard::Left)){
                    if(decalage > 0){
                        decalage -= 0.5;
                    }
                    else{
                        decalage = 0;
                    }
                }
            }
        }

        window.clear();
        if(!parametre and !choix_niveau){
            window.draw(texteTitre);
            window.draw(texteSousTitre);
            window.draw(boutonJouer);
            window.draw(boutonEditeur);
            window.draw(boutonParametre);
            window.draw(boutonQuitter);
            window.draw(texteJouer);
            window.draw(texteEditeur);
            window.draw(texteParametre);
            window.draw(texteQuitter);
            window.draw(texteCredits);
            window.draw(texteCredits2);
        }
        if(choix_niveau){
            for(int i = 0; i < 5; i++){
                window.draw(boutonsNiveaux[i]);
                window.draw(textesNiveaux[i]);
            }
            window.draw(boutonCharger);
            window.draw(texteCharger);
            window.draw(boutonRetour);
            window.draw(texteRetour);
        }
        if(parametre){
            texteVolume.setString("Volume : " + to_string(volume) + "%");
            texteVolume.setPosition((window.getSize().x-texteVolume.getGlobalBounds().width)/2,200);

            barreVolume2.setSize(Vector2f(6*volume,10));
            curseurVolume.setPosition((1320-curseurVolume.getGlobalBounds().width)/2+6*volume,290);

            texteDecalage.setString("Decalage : " + to_string(decalage));
            texteDecalage.setPosition((window.getSize().x-texteDecalage.getGlobalBounds().width)/2,400);

            barreDecalage2.setSize(Vector2f(120*decalage,10));
            curseurDecalage.setPosition((1320-curseurDecalage.getGlobalBounds().width)/2+120*decalage,490);

            window.draw(texteVolume);
            window.draw(barreVolume);
            window.draw(barreVolume2);
            window.draw(curseurVolume);
            window.draw(texteDecalage);
            window.draw(barreDecalage);
            window.draw(barreDecalage2);
            window.draw(curseurDecalage);
            window.draw(texteConseil);
            window.draw(texteConseil2);
            window.draw(boutonRetour);
            window.draw(texteRetour);
        }
        
        music.setVolume(volume);
        window.display();
    }
    music.stop();
    return 0;
}