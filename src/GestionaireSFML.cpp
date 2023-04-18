#include "GestionaireSFML.h"

#include <iostream>
#include <math.h>
using namespace std;
using namespace sf;

GestionSFML::GestionSFML()
{   
    ChargerTerrain("data/circuits/test.json");
    float l, h;

    
    for (int i = 0; i < 1; i++)
    {   //génération de sprite
        if(!text_voiture.loadFromFile("data/cars/F1.png")){
            cout << "Problème de chargement de texture" << endl;
        }
        text_voiture.setSmooth(true);
        Vecteur taille(text_voiture.getSize().x,text_voiture.getSize().y);
        float proportion = taille.y/taille.x;
        taille=Vecteur(5/taille.y,5/taille.y);
        
        Vecteur Hitbox(proportion,1);   
        voiture.setTexture(text_voiture);
        voiture.setScale(taille.x,taille.y);
        voiture.setOrigin(text_voiture.getSize().x/2,text_voiture.getSize().y/2);
        //ajoute une voiture de la classe voiture
        ajouterVoiture(Voiture(Moteur(),Roues(),796,0.14,Hitbox.x,Hitbox.y,0,0,0,0,0));
        cout<<"Hitbox : "<<Hitbox.x<<" "<<Hitbox.y<<endl;
        cout << "Chargement voiture ok" << endl;
    }
    Vecteur hitbox;
    Vecteur position;
    for (int i = 0; i < terrain.getNbProps(); i++)
    {   l=terrain.getProp(i).getLong();
        h=terrain.getProp(i).getLarg();
        obstacles.push_back(RectangleShape(Vector2f(l,h)));
        cout << obstacles[i].getOrigin().x << " " << obstacles[i].getOrigin().y << endl;
        cout << "vers "<< l/2 << " " << h/2 << endl;
        obstacles[i].setOrigin(l/2,h/2);
        obstacles[i].setPosition(terrain.getProp(i).getX(),terrain.getProp(i).getY());
        obstacles[i].setRotation(terrain.getProp(i).getRotation()*180/M_PI);
        cout << "props ok" << endl;
    }

    text_fond.loadFromFile("data/circuits/circuit.png");
    fond.setTexture(text_fond);
    fond.setScale(0.1,0.1);

    zoom = 1;
    rotation = 0;
}

GestionSFML::~GestionSFML()
{   window.close();
    obstacles.clear();
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
            
            case Keyboard::Up :
                action.accelere=true;
                break;
            
            case Keyboard::Down :
                action.freine=true;
                break;
            
            case Keyboard::Left :
                action.gauche=true;
                break;
            
            case Keyboard::Right :
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
            
            case Keyboard::Up :
                action.accelere=false;
                break;
            
            case Keyboard::Down :
                action.freine=false;
                break;
            
            case Keyboard::Left :
                action.gauche=false;
                break;
            
            case Keyboard::Right :
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

string affiche_temps(float t){
    int minutes = floor(t/60);
    t-=minutes*60;
    int secondes = floor(t);
    t-=secondes;
    return to_string(minutes) + "'" + to_string(secondes) + "\"" + to_string(int(t*1000));
}


void GestionSFML::boucleJeuSFML()
{   RenderWindow window(VideoMode(1280,720),"Vroum",Style::Fullscreen);
    window.setFramerateLimit(120);
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
        voiture.setPosition(pos.x,pos.y);
        voiture.setRotation(tab_voit[0].getAngle()*180/M_PI-90);
        
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
        
        texte_chrono.setString(affiche_temps(temps_au_tour.getElapsedTime().asSeconds()));
        
        // On affiche le jeu
        afficherJeuSFML(window);
        
        View vue(voiture.getPosition(), Vector2f(96.f, 48.f));
        vue.move(cos(getVoiture(0).getAngle()) * 1,1*sin(getVoiture(0).getAngle()));
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
    // Dessins
    window.clear(Color(0,200,0));
    
    window.draw(fond);
    window.draw(voiture);
    
    RectangleShape hit_box(Vector2f(getVoiture(0).getHitbox().x*2, getVoiture(0).getHitbox().y*2));
    
    hit_box.setOrigin(getVoiture(0).getHitbox().x, getVoiture(0).getHitbox().y);
    
    hit_box.setRotation(getVoiture(0).getAngle()*180/M_PI);
    hit_box.setFillColor(Color(255,0,0,150));
    //RectangleShape hit_box(Vector2f(10,10));
    hit_box.setPosition(voiture.getPosition());
    window.draw(hit_box);
    for (int i = 0; i < terrain.getNbProps(); i++)
    {
        window.draw(obstacles[i]);
    }
}