#include "Menu.h"
#include <iostream>
#include <string>

using namespace std;

int Menu::boucleMenu(RenderWindow & window){

    RectangleShape boutonJeu;
    boutonJeu.setFillColor(Color::Transparent);
    boutonJeu.setOutlineThickness(5);
    boutonJeu.setOutlineColor(Color::White);
    boutonJeu.setSize(Vector2f(300,100));
    boutonJeu.setPosition(810,500);

    RectangleShape boutonEditeur;
    boutonEditeur.setFillColor(Color::Transparent);
    boutonEditeur.setOutlineThickness(5);
    boutonEditeur.setOutlineColor(Color::White);
    boutonEditeur.setSize(Vector2f(300,100));
    boutonEditeur.setPosition(810,700);

    RectangleShape boutonQuitter;
    boutonQuitter.setFillColor(Color::Transparent);
    boutonQuitter.setOutlineThickness(5);
    boutonQuitter.setOutlineColor(Color::White);
    boutonQuitter.setSize(Vector2f(300,100));
    boutonQuitter.setPosition(810,900);

    Font font;
    font.loadFromFile("data/fonts/F1.ttf");

    Text texteTitre;
    texteTitre.setFont(font);
    texteTitre.setCharacterSize(100);
    texteTitre.setFillColor(Color::Red);
    texteTitre.setString("The Great Competition :");
    texteTitre.setPosition(300,0);

    Text texteSousTitre;
    texteSousTitre.setFont(font);
    texteSousTitre.setCharacterSize(100);
    texteSousTitre.setFillColor(Color::Red);
    texteSousTitre.setString("Fast One");
    texteSousTitre.setPosition(600,100);

    Text texteJeu;
    texteJeu.setFont(font);
    texteJeu.setCharacterSize(50);
    texteJeu.setString("Jeu");
    texteJeu.setPosition(905,515);

    Text texteEditeur;
    texteEditeur.setFont(font);
    texteEditeur.setCharacterSize(50);
    texteEditeur.setString("Editeur");
    texteEditeur.setPosition(858,715);

    Text texteQuitter;
    texteQuitter.setFont(font);
    texteQuitter.setCharacterSize(50);
    texteQuitter.setString("Quitter");
    texteQuitter.setPosition(858,915);

    while (window.isOpen()){
        Event event;
        while (window.pollEvent(event)){
            if (event.type == Event::Closed)
                window.close();
            if (event.type == Event::KeyPressed){
                if (event.key.code == Keyboard::Escape){
                    return 0;
                }
            }
            if (event.type == Event::MouseButtonPressed){
                if (event.mouseButton.button == Mouse::Left){
                    if (boutonJeu.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)){
                        return 1;
                    }
                    if (boutonEditeur.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)){
                        return 2;
                    }
                    if (boutonQuitter.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)){
                        return 3;
                    }
                }
            }
        }

        if(boutonJeu.getGlobalBounds().contains(Mouse::getPosition(window).x, Mouse::getPosition(window).y)){
            boutonJeu.setOutlineColor(Color::Red);
        }
        else{
            boutonJeu.setOutlineColor(Color::White);
        }

        if(boutonEditeur.getGlobalBounds().contains(Mouse::getPosition(window).x, Mouse::getPosition(window).y)){
            boutonEditeur.setOutlineColor(Color::Red);
        }
        else{
            boutonEditeur.setOutlineColor(Color::White);
        }

        if(boutonQuitter.getGlobalBounds().contains(Mouse::getPosition(window).x, Mouse::getPosition(window).y)){
            boutonQuitter.setOutlineColor(Color::Red);
        }
        else{
            boutonQuitter.setOutlineColor(Color::White);
        }

        window.clear();
        window.draw(texteTitre);
        window.draw(texteSousTitre);
        window.draw(boutonJeu);
        window.draw(boutonEditeur);
        window.draw(boutonQuitter);
        window.draw(texteJeu);
        window.draw(texteEditeur);
        window.draw(texteQuitter);
        window.display();
    }
    return 0;
}

/*
bool Menu_Pause(void)
{   string option;
    do{
        cout<<"entrer p pour sortir"<<endl;
        cin>>option;
    } while ( option != "p");
    return 1;
};

bool Menu_Principal(void)
{   string option;
    do{
        cout<<"entrer p pour sortir"<<endl;
        cin>>option;
    } while ( option != "p");
    return 1;
}
*/   