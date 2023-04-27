#include "Menu.h"
#include <iostream>
#include <string>
#include <SFML/Audio.hpp>

using namespace std;
using namespace sf;

void initBouton(RectangleShape & rectangle, int y, int largeur, int hauteur){
    rectangle.setFillColor(Color::Transparent);
    rectangle.setOutlineThickness(3);
    rectangle.setOutlineColor(Color::White);
    rectangle.setSize(Vector2f(largeur,hauteur));
    rectangle.setPosition((1920-largeur)/2, y);
}

void initCurseur(RectangleShape & rectangle, int y, int largeur, int hauteur){
    initBouton(rectangle, y, largeur, hauteur);
    rectangle.setFillColor(Color::White);
}

void initTexte(Text & texte, Font & font, int taille, string txt, int y){
    texte.setFont(font);
    texte.setCharacterSize(taille);
    texte.setString(txt);
    texte.setFillColor(Color::White);
    texte.setPosition((1920-texte.getLocalBounds().width)/2, y+15);
}

void initTitre(Text & texte, Font & font, int taille, string txt, int y){
    initTexte(texte, font, taille, txt, y);
    texte.setFillColor(Color::Red);
}

int Menu::boucleMenu(RenderWindow & window, int & volume, float & decalage){

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
    initBouton(boutonJouer, 450, 400, 100);

    RectangleShape boutonEditeur;
    initBouton(boutonEditeur, 600, 400, 100);

    RectangleShape boutonParametre;
    initBouton(boutonParametre, 750, 400, 100);

    RectangleShape boutonQuitter;
    initBouton(boutonQuitter, 900, 400, 100);

    RectangleShape barreVolume;
    initBouton(barreVolume, 300, 600, 10);

    RectangleShape barreVolume2;
    initCurseur(barreVolume2, 300, 600, 10);

    RectangleShape curseurVolume;
    initCurseur(curseurVolume, 300, 10, 30);

    RectangleShape barreDecalage;
    initBouton(barreDecalage, 500, 600, 10);

    RectangleShape barreDecalage2;
    initCurseur(barreDecalage2, 500, 600, 10);

    RectangleShape curseurDecalage;
    initCurseur(curseurDecalage, 500, 10, 30);

    RectangleShape boutonRetour;
    initBouton(boutonRetour, 900, 400, 100);

    //TEXTES=======================================================================================

    Font font;
    font.loadFromFile("data/fonts/F1.ttf");

    Text texteTitre;
    initTitre(texteTitre, font, 100, "The Great Competition :", 50);

    Text texteSousTitre;
    initTitre(texteSousTitre, font, 100, "Fast One", 175);

    Text texteJouer;
    initTexte(texteJouer, font, 50, "Jouer", 450);

    Text texteEditeur;
    initTexte(texteEditeur, font, 50, "Editeur", 600);

    Text texteParametre;
    initTexte(texteParametre, font, 50, "Parametres", 750);

    Text texteQuitter;
    initTexte(texteQuitter, font, 50, "Quitter", 900);

    Text texteCredits;
    initTexte(texteCredits, font, 25, "version alpha", 0);
    texteCredits.setPosition(window.getSize().x*0.84, window.getSize().y*0.9); 

    Text texteCredits2;
    initTexte(texteCredits2, font, 25, "by Ninotnas & Sipior", 0);
    texteCredits2.setPosition(window.getSize().x*0.84, window.getSize().y*0.95);

    Text texteVolume;
    initTexte(texteVolume, font, 50, "Volume : " + to_string(volume), 200);

    Text texteDecalage;
    initTexte(texteDecalage, font, 50, "Decalage : " + to_string(decalage), 600);

    Text texteConseil;
    initTexte(texteConseil, font, 25, "Pour regler le volume, utilisez les fleches HAUT et BAS", 700);

    Text texteConseil2;
    initTexte(texteConseil2, font, 25, "Pour regler le decalage, utilisez les fleches GAUCHE et DROITE", 750);

    Text texteRetour;
    initTexte(texteRetour, font, 50, "Retour", 900);


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
                        if (boutonJouer.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)){
                            choix_niveau = true;
                        }
                        if (boutonEditeur.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)){
                            return 2;
                        }
                        if (boutonParametre.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)){
                            parametre = true;
                        }
                        if (boutonQuitter.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)){
                            return 3;
                        }
                    }
                }
                if(boutonJouer.getGlobalBounds().contains(Mouse::getPosition(window).x, Mouse::getPosition(window).y)){
                    boutonJouer.setOutlineColor(Color::Red);
                    boutonJouer.setFillColor(Color(32,32,32));
                }
                else{
                    boutonJouer.setOutlineColor(Color::White);
                    boutonJouer.setFillColor(Color::Transparent);
                }

                if(boutonEditeur.getGlobalBounds().contains(Mouse::getPosition(window).x, Mouse::getPosition(window).y)){
                    boutonEditeur.setOutlineColor(Color::Red);
                    boutonEditeur.setFillColor(Color(32,32,32));
                }
                else{
                    boutonEditeur.setOutlineColor(Color::White);
                    boutonEditeur.setFillColor(Color::Transparent);
                }

                if(boutonParametre.getGlobalBounds().contains(Mouse::getPosition(window).x, Mouse::getPosition(window).y)){
                    boutonParametre.setOutlineColor(Color::Red);
                    boutonParametre.setFillColor(Color(32,32,32));
                }
                else{
                    boutonParametre.setOutlineColor(Color::White);
                    boutonParametre.setFillColor(Color::Transparent);
                }
                
                if(boutonQuitter.getGlobalBounds().contains(Mouse::getPosition(window).x, Mouse::getPosition(window).y)){
                    boutonQuitter.setOutlineColor(Color::Red);
                    boutonQuitter.setFillColor(Color(32,32,32));
                }
                else{
                    boutonQuitter.setOutlineColor(Color::White);
                    boutonQuitter.setFillColor(Color::Transparent);
                }
            }
            else{ //Menu parametre ================================================================
                if(event.type == Event::KeyPressed){
                    if(event.key.code == Keyboard::Escape){
                        choix_niveau = false;
                        parametre = false;
                    }
                }
                if (event.type == Event::MouseButtonPressed){
                    if (event.mouseButton.button == Mouse::Left){
                        if (boutonRetour.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)){
                            choix_niveau = false;
                            parametre = false;
                        }
                    }
                }
                if(boutonRetour.getGlobalBounds().contains(Mouse::getPosition(window).x, Mouse::getPosition(window).y)){
                    boutonRetour.setOutlineColor(Color::Red);
                    boutonRetour.setFillColor(Color(32,32,32));
                }
                else{
                    boutonRetour.setOutlineColor(Color::White);
                    boutonRetour.setFillColor(Color::Transparent);
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
                    if(decalage < 5){
                        decalage += 0.5;
                    }
                }
                if(Keyboard::isKeyPressed(Keyboard::Left)){
                    if(decalage > 0){
                        decalage -= 0.5;
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
            window.draw(boutonRetour);
            window.draw(texteRetour);
        }
        if(parametre){
            texteVolume.setString("Volume : " + to_string(volume) + "%");
            texteVolume.setPosition((1920-texteVolume.getGlobalBounds().width)/2,200);

            barreVolume2.setSize(Vector2f(6*volume,10));
            curseurVolume.setPosition((1320-curseurVolume.getGlobalBounds().width)/2+6*volume,290);

            texteDecalage.setString("Decalage : " + to_string(decalage));
            texteDecalage.setPosition((1920-texteDecalage.getGlobalBounds().width)/2,400);

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