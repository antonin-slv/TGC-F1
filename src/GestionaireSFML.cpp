#include "GestionaireSFML.h"

#include <iostream>
#include <math.h>
using namespace std;
using namespace sf;

GestionSFML::GestionSFML()
{   
    
    ChargerTerrain("data/circuits/test.json");

    //RenderWindow window(VideoMode(1280,720),"Vroum",Style::Fullscreen);

    setframe_time(0);
    float l, h;

    for (int i = 0; i < 1; i++)
    {   
        if(!text_voiture.loadFromFile("data/cars/F1.png")){
            cout << "Problème de chargement de texture" << endl;
        }
        text_voiture.setSmooth(true);
        voiture.setTexture(text_voiture);
        voiture.setScale(Vector2f(0.01,0.01));
        voiture.setOrigin(text_voiture.getSize().x/2,text_voiture.getSize().y/2);
        cout << "Chargement voiture ok" << endl;
    }
    Vecteur hitbox;
    Vecteur position;
    for (int i = 0; i < terrain.getNbProps(); i++)
    {   l=terrain.getProp(i).getLong();
        h=terrain.getProp(i).getLarg();
        obstacles.push_back(RectangleShape(Vector2f(l,h)));
        cout<<obstacles[i].getOrigin().x<<" "<<obstacles[i].getOrigin().y<<endl;
        cout<<"vers"<<l/2<<" "<<h/2<<endl;
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

void GestionSFML::initWindow(int width, int height, string title)
{   //RenderWindow window(VideoMode(width,height),title); 
}

GestionSFML::~GestionSFML()
{   window.close();
    obstacles.clear();
}

void getActionClavier(Event event, ActionClavier & action)
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
            default:
                break;
        }
    }
}


void GestionSFML::boucleJeuSFML()
{   RenderWindow window(VideoMode(1280,720),"Vroum",Style::Fullscreen);
    window.setFramerateLimit(120);
    //centre la vue sur (0,0) avec un carré de 640*360 px
    Clock clock;
    clock.restart();
    
    Clock frames;

    Font font;
    if (!font.loadFromFile("data/fonts/Papyrus.ttf")){
        cout << "Souci de police" << endl;
    }

    Text text;

    // select the font
    text.setFont(font); // font is a Font
    // set the character size
    text.setCharacterSize(50); // in pixels, not points!
    text.setScale(0.025,0.025);
    // set the color
    text.setFillColor(Color::White);
    
    long int nb_frames=0;
    float temps=0;
    cout << "debut ok" << endl;
    ActionClavier action;

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
                        getActionClavier(event,action);
                        break;
                }
            }
            else if (event.type == Event::KeyReleased){

                switch (event.key.code){
                    default:
                        getActionClavier(event,action);
                        break;
                }
            }

            
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
                        "temps in game :" + to_string(temps) + "\n s contre : " + to_string(clock.getElapsedTime().asSeconds()) + "s réelles\n"
                        "frame time : " + to_string(frame_time) + "\n"
                        "fps : " + to_string(1/frame_time) + "\n");
        
        
        // Clear en noir
        window.clear(Color::Green);
        text.setPosition(window.mapPixelToCoords(Vector2i(10, 10)));
        
        window.draw(fond);
        window.draw(text);
        // On affiche le jeu
        afficherJeuSFML(window);
    }
    cout<<"nb frames : "<<nb_frames<<endl;
    cout<<"temps : "<<temps<<endl;
    cout<<"fps_moy : "<<nb_frames/temps<<endl;
}


void GestionSFML::afficherJeuSFML(RenderWindow & window)
{   
    // Dessins
    
    window.draw(voiture);
    for (int i = 0; i < terrain.getNbProps(); i++)
    {
        window.draw(obstacles[i]);
    }
    
    
    // Affichage
    
    window.setView(View(voiture.getPosition(), Vector2f(128.f, 72.f)));
    window.display();

}



