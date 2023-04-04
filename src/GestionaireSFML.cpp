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
    {   l=tab_voit[i].getLongueur();
        h=tab_voit[i].getLargeur();
        if(!text_voiture.loadFromFile("data/cars/F1.png")){
            cout << "Problème de chargement de texture" << endl;
        }
        text_voiture.setSmooth(true);
        voiture.setTexture(text_voiture);
        voiture.setScale(Vector2f(0.01,0.01));
        voiture.setOrigin(l/2,h/2);
        cout << "Chargement voiture ok" << endl;
    }
    
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

void GestionSFML::boucleJeuSFML()
{   RenderWindow window(VideoMode(1280,720),"Vroum",Style::Fullscreen);
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
    
    bool ACTION=false;
    float temps=0;
    cout << "debut ok" << endl;
    while (window.isOpen()){
    // On traite tous les évènements de la fenêtre qui ont été générés depuis la dernière itération de la boucle
        Event event;
        ACTION=false;
        temps+=frame_time;
        frames.restart();
        while (window.pollEvent(event)){
            // Partie physique
            //1-> on fait tout accélérer/tourner.
            if (event.type == Event::KeyPressed && !ACTION){
                ACTION=true;
                switch (event.key.code){
                    case Keyboard::Z :
                        update('z');
                        break;
                    case Keyboard::S :
                        update('s');
                        break;
                    case Keyboard::Q :
                        update('q');
                        break;
                    case Keyboard::D :
                        update('d');
                        break;
                    case Keyboard::Escape :
                        window.close();
                        break;
                    case Keyboard::A :
                        window.close();
                        break;
                    default:
                        update(' ');
                        break;
                }
            }
            //2-> on applique la résistance de l'air
            
            //3 -> update vitesse/position

            //3-> on teste les collisions
        }
        if (!ACTION) 
        {   update(' ');
        }

        //actualise position des voitures du jeu
        voiture.setPosition(tab_voit[0].getX(),tab_voit[0].getY());
        voiture.setRotation(tab_voit[0].getAngle()*180/M_PI-90);
        
        // Fermeture de la fenêtre avec la croix (inutile pour le moment)
        if (event.type == Event::Closed){
            window.close();
        }
        text.setString("Vitesse : " + to_string(getVoiture(0).getVitesse()*3.6) + " km/h \n" +
                        "Position : " + to_string(getVoiture(0).getX()) + " , " + to_string(getVoiture(0).getY()) + "\n" +
                        "Orientation : " + to_string(getVoiture(0).getAngle()*180/M_PI) + "\n" +
                        "temps in game :" + to_string(temps) + "\n s contre : " + to_string(clock.getElapsedTime().asSeconds()) + "s réelles");
        
        
        // Clear en noir
        window.clear(Color::Black);
        text.setPosition(window.mapPixelToCoords(Vector2i(10, 10)));
        
        
        window.draw(text);
        // On affiche le jeu
        afficherJeuSFML(window);
        frame_time=frames.getElapsedTime().asSeconds()*15;
  }
}


void GestionSFML::afficherJeuSFML(RenderWindow & window)
{   
    // Dessins
    window.draw(fond);
    window.draw(voiture);
    for (int i = 0; i < terrain.getNbProps(); i++)
    {
        window.draw(obstacles[i]);
    }
    
    
    // Affichage
    
    window.setView(View(voiture.getPosition(), Vector2f(128.f, 72.f)));
    window.display();

}

