#include "Menu.h"
#include <iostream>
#include <string>
#include <SFML/Audio.hpp>

using namespace std;
using namespace sf;

int Menu::boucleMenu(RenderWindow & window, int & volume, float & decalage){

    //INITIALISATION===============================================================================
    window.setView(window.getDefaultView());

    bool parametre = false;

    Music music;
    music.openFromFile("data/sounds/menu.wav");
    music.setVolume(volume);
    music.setLoop(true);
    music.play();

    RectangleShape boutonJeu;
    boutonJeu.setFillColor(Color::Transparent);
    boutonJeu.setOutlineThickness(3);
    boutonJeu.setOutlineColor(Color::White);
    boutonJeu.setSize(Vector2f(400,100));
    boutonJeu.setPosition((1920-boutonJeu.getSize().x)/2, 450);

    RectangleShape boutonEditeur;
    boutonEditeur.setFillColor(Color::Transparent);
    boutonEditeur.setOutlineThickness(3);
    boutonEditeur.setOutlineColor(Color::White);
    boutonEditeur.setSize(Vector2f(400,100));
    boutonEditeur.setPosition((1920-boutonEditeur.getSize().x)/2, 600);

    RectangleShape boutonParametre;
    boutonParametre.setFillColor(Color::Transparent);
    boutonParametre.setOutlineThickness(3);
    boutonParametre.setOutlineColor(Color::White);
    boutonParametre.setSize(Vector2f(400,100));
    boutonParametre.setPosition((1920-boutonParametre.getSize().x)/2, 750);

    RectangleShape boutonQuitter;
    boutonQuitter.setFillColor(Color::Transparent);
    boutonQuitter.setOutlineThickness(3);
    boutonQuitter.setOutlineColor(Color::White);
    boutonQuitter.setSize(Vector2f(400,100));
    boutonQuitter.setPosition((1920-boutonQuitter.getSize().x)/2, 900);

    RectangleShape boutonRetour;
    boutonRetour.setFillColor(Color::Transparent);
    boutonRetour.setOutlineThickness(3);
    boutonRetour.setOutlineColor(Color::White);
    boutonRetour.setSize(Vector2f(400,100));
    boutonRetour.setPosition((1920-boutonRetour.getSize().x)/2, 900);

    

    Font font;
    font.loadFromFile("data/fonts/F1.ttf");

    Text texteTitre;
    texteTitre.setFont(font);
    texteTitre.setCharacterSize(100);
    texteTitre.setFillColor(Color::Red);
    texteTitre.setString("The Great Competition :");
    texteTitre.setPosition((1920-texteTitre.getGlobalBounds().width)/2,50);

    Text texteSousTitre;
    texteSousTitre.setFont(font);
    texteSousTitre.setCharacterSize(100);
    texteSousTitre.setFillColor(Color::Red);
    texteSousTitre.setString("Fast One");
    texteSousTitre.setPosition((1920-texteSousTitre.getGlobalBounds().width)/2,175);

    Text texteJeu;
    texteJeu.setFont(font);
    texteJeu.setCharacterSize(50);
    texteJeu.setString("Jeu");
    texteJeu.setPosition((1920-texteJeu.getGlobalBounds().width)/2-5,465);

    Text texteEditeur;
    texteEditeur.setFont(font);
    texteEditeur.setCharacterSize(50);
    texteEditeur.setString("Editeur");
    texteEditeur.setPosition((1920-texteEditeur.getGlobalBounds().width)/2,615);

    Text texteParametre;
    texteParametre.setFont(font);
    texteParametre.setCharacterSize(50);
    texteParametre.setString("Parametres");
    texteParametre.setPosition((1920-texteParametre.getGlobalBounds().width)/2,765);

    Text texteQuitter;
    texteQuitter.setFont(font);
    texteQuitter.setCharacterSize(50);
    texteQuitter.setString("Quitter");
    texteQuitter.setPosition((1920-texteQuitter.getGlobalBounds().width)/2,915);

    Text credits;
    credits.setFont(font);
    credits.setCharacterSize(25);
    credits.setString("version alpha");
    credits.setPosition(5*window.getSize().x/6,window.getSize().y*0.90); 

    Text credits2;
    credits2.setFont(font);
    credits2.setCharacterSize(25);
    credits2.setString("by : Ninotnas & Sipior");
    credits2.setPosition(5*window.getSize().x/6,window.getSize().y*0.95);

    Text texteVolume;
    texteVolume.setFont(font);
    texteVolume.setCharacterSize(50);
    texteVolume.setString("Volume : " + to_string(volume));
    texteVolume.setPosition((1920-texteVolume.getGlobalBounds().width)/2,200);

    Text texteDecalage;
    texteDecalage.setFont(font);
    texteDecalage.setCharacterSize(50);
    texteDecalage.setString("Decalage : " + to_string(decalage));
    texteDecalage.setPosition((1920-texteDecalage.getGlobalBounds().width)/2,500);

    Text texteRetour;
    texteRetour.setFont(font);
    texteRetour.setCharacterSize(50);
    texteRetour.setString("Retour");
    texteRetour.setPosition((1920-texteRetour.getGlobalBounds().width)/2,915);


    //BOUCLE PRINCIPALE============================================================================
    while (window.isOpen()){
        Event event;
        while (window.pollEvent(event)){
            if (event.type == Event::Closed){
                window.close();
            }
            if(!parametre){ //Menu principal ======================================================
                if (event.type == Event::MouseButtonPressed){
                    if (event.mouseButton.button == Mouse::Left){
                        if (boutonJeu.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)){
                            return 1;
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
                if(boutonJeu.getGlobalBounds().contains(Mouse::getPosition(window).x, Mouse::getPosition(window).y)){
                    boutonJeu.setOutlineColor(Color::Red);
                    boutonJeu.setFillColor(Color(32,32,32));
                }
                else{
                    boutonJeu.setOutlineColor(Color::White);
                    boutonJeu.setFillColor(Color::Transparent);
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
                        parametre = false;
                    }
                }
                if (event.type == Event::MouseButtonPressed){
                    if (event.mouseButton.button == Mouse::Left){
                        if (boutonRetour.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)){
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
                    if(volume < 100){
                        volume+=5;
                    }
                }
                if(Keyboard::isKeyPressed(Keyboard::Down)){
                    if(volume > 0){
                        volume-=5;
                    }
                }
                if(Keyboard::isKeyPressed(Keyboard::Right)){
                    if(decalage < 5){
                        decalage+=0.5;
                    }
                }
                if(Keyboard::isKeyPressed(Keyboard::Left)){
                    if(decalage > 0){
                        decalage-=0.5;
                    }
                }
            }
        }

        window.clear();
        if(!parametre){
            window.draw(texteTitre);
            window.draw(texteSousTitre);
            window.draw(boutonJeu);
            window.draw(boutonEditeur);
            window.draw(boutonParametre);
            window.draw(boutonQuitter);
            window.draw(texteJeu);
            window.draw(texteEditeur);
            window.draw(texteParametre);
            window.draw(texteQuitter);
            window.draw(credits);
            window.draw(credits2);
        }
        else{
            texteVolume.setString("Volume : " + to_string(volume) + "%");
            texteVolume.setPosition((1920-texteVolume.getGlobalBounds().width)/2,200);

            texteDecalage.setString("Decalage : " + to_string(decalage));
            texteDecalage.setPosition((1920-texteDecalage.getGlobalBounds().width)/2,400);

            window.draw(texteVolume);
            window.draw(texteDecalage);
            window.draw(boutonRetour);
            window.draw(texteRetour);
        }
        
        music.setVolume(volume);
        window.display();
    }
    music.stop();
    return 0;
}