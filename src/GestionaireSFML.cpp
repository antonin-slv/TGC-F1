#include "GestionaireSFML.h"

#include <iostream>
#include <math.h>
using namespace std;
using namespace sf;

GestionSFML::GestionSFML()
{   
    ChargerTerrain("data/circuits/test.json");
    interface.loadTerrain(terrain,"");
    Voiture Voit_temp;
    interface.loadVoiture(Voit_temp,"data/cars/F1.png");
    ajouterVoiture(Voit_temp);

    text_fond.loadFromFile("data/circuits/circuit.png");
    fond.setTexture(text_fond);
    fond.setScale(0.1,0.1);

    zoom = 1;
}

GestionSFML::~GestionSFML()
{   
}

void getActionClavier(Event event, ActionClavier & action, Clock & _temps_au_tour)
{   if (event.type == Event::KeyPressed){
        switch (event.key.code){
            case Keyboard::Z :
                action.accelere=true;
                break;
            case Keyboard::S :
                action.freine=true;
                break;
            case Keyboard::Q :
                action.gauche=true;
                break;
            case Keyboard::D :
                action.droite=true;
                break;
            default:
                break;
        }
    }
    else if (event.type == Event::KeyReleased){

        switch (event.key.code){
            case Keyboard::Z :
                action.accelere=false;
                break;
            case Keyboard::S :
                action.freine=false;
                break;
            case Keyboard::Q :
                action.gauche=false;
                break;
            case Keyboard::D :
                action.droite=false;
                break;
            case Keyboard::R :
                _temps_au_tour.restart();
                break;
            default:
                break;
        }
    }
}


void GestionSFML::boucleJeuSFML(RenderWindow & window)
{   window.setFramerateLimit(120);
    Clock clock;
    clock.restart();
    
    Clock frames;

    Font font;
    font.loadFromFile("data/fonts/Consolas.ttf");

    Text text;

    // select the font
    text.setFont(font); // font is a Font
    // set the character size
    text.setCharacterSize(50); // in pixels, not points!
    text.setScale(0.025,0.025);
    
    long int nb_frames = 0;
    float temps = 0;
    cout << "debut ok" << endl;
    ActionClavier action;
    Clock temps_au_tour;
    Text texte_chrono;
    texte_chrono.setFont(font);
    texte_chrono.setCharacterSize(50);
    texte_chrono.setScale(0.025,0.025);

    while (window.isOpen()){
    // On traite tous les évènements de la fenêtre qui ont été générés depuis la dernière itération de la boucle
        Event event;
        nb_frames++;
        temps+=frame_time;
        frame_time=frames.restart().asSeconds();
        while (window.pollEvent(event)){
            // Partie physique
            //1-> on fait tout accélérer/tourner.
            if (event.type == Event::KeyPressed){

                switch (event.key.code){
                    case Keyboard::Escape :
                        window.close();
                        break;
                    case Keyboard::A :
                        window.close();
                        break;
                    default:
                        break;
                }
            }
            getActionClavier(event, action, temps_au_tour);            
        }

        //fait tout le bouleau d'update du jeu
        update(action);

        //actualise position des voitures du jeu
        Vecteur pos=getVoiture(0).getPos();
        
        // Fermeture de la fenêtre avec la croix (inutile pour le moment)
        if (event.type == Event::Closed){
            window.close();
        }
        text.setString("Vitesse : " + to_string(getVoiture(0).getVitesse()*3.6) + " km/h \n" +
                        "Position : " + to_string(pos.x) + " , " + to_string(pos.y) + "\n" +
                        "Orientation : " + to_string(getVoiture(0).getAngle()*180/M_PI) + "\n" +
                        "temps in game :" + to_string(temps) + "\n s contre : " + to_string(clock.getElapsedTime().asSeconds()) + "s IRL\n"
                        "frame time : " + to_string(frame_time) + "\n"
                        "fps : " + to_string(1/frame_time) + "\n");
        
        texte_chrono.setString(to_string(temps_au_tour.getElapsedTime().asSeconds()) + " secondes");
        
        // On affiche le jeu
        afficherJeuSFML(window);
        
        View vue(interface.voiture.getPosition(), Vector2f(96.f, 48.f));
        vue.move(cos(getVoiture(0).getAngle()) * 7,7*sin(getVoiture(0).getAngle()));
        //vue.move(sin(getVoiture(0).getAngle()) * 15,15*cos(getVoiture(0).getAngle()));
        //vue.setRotation(voiture.getRotation()+180);
        window.setView(vue);
        afficherDebug(window, text, texte_chrono);
        window.display();
    }
    cout << "nb frames : " << nb_frames << endl;
    cout << "temps : " << temps << endl;
    cout << "fps_moy : " << nb_frames/temps << endl;
}

void GestionSFML::afficherDebug(RenderWindow & window, Text & text, Text & texte_chrono)
{   
    // Dessins
    text.setPosition(window.mapPixelToCoords(Vector2i(10, 10)));
    texte_chrono.setPosition(window.mapPixelToCoords(Vector2i(1750, 10)));
    
    window.draw(text);
    window.draw(texte_chrono);

}

void GestionSFML::afficherJeuSFML(RenderWindow & window)
{   
    window.clear();
    window.draw(fond);
    interface.drawVoiture(window, tab_voit[0]);
    interface.drawTerrain(window);
}
