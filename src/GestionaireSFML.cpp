#include "GestionaireSFML.h"

#include <iostream>
#include <math.h>
using namespace std;
using namespace sf;

GestionSFML::GestionSFML()
{   
    
    ChargerTerrain("data/circuits/test.json");

    //RenderWindow window(VideoMode(1280,720),"Vroum",Style::Fullscreen);

    setframe_time(0.016);
    float l, h;

    for (int i = 0; i < nb_voit; i++)
    {   l=tab_voit[i].getLongueur();
        h=tab_voit[i].getLargeur();
        voitures.push_back(RectangleShape(Vector2f(l,h)));
        voitures[i].setFillColor(Color(255,0,0));
        cout<<voitures[i].getOrigin().x<<" "<<voitures[i].getOrigin().y<<endl;
        cout<<"vers"<<l/2<<" "<<h/2<<endl;
        voitures[i].setOrigin(l/2,h/2);
        voitures[i].setPosition(getVoiture(i).getX(),getVoiture(i).getY());
        voitures[i].setRotation(getVoiture(i).getAngle()*180/M_PI);
        Texture texture;
        if (!texture.loadFromFile("data/cars/F1.png"))
            {   cout << "Erreur lors du chargement de l'image" << endl;
        }
        Sprite sprite;
        sprite.setTexture(texture);
        sprites.push_back(sprite);

    }

    for (int i = 0; i < terrain.getNbProps(); i++)
    {   l=terrain.getProp(i).getLong();
        h=terrain.getProp(i).getLarg();
        obstacles.push_back(RectangleShape(Vector2f(l,h)));
        cout<<obstacles[i].getOrigin().x<<" "<<obstacles[i].getOrigin().y<<endl;
        cout<<"vers"<<l/2<<" "<<h/2<<endl;
        obstacles[i].setOrigin(l/2,h/2);
        obstacles[i].setFillColor(Color(0,0,255));
        obstacles[i].setPosition(terrain.getProp(i).getX(),terrain.getProp(i).getY());
        obstacles[i].setRotation(terrain.getProp(i).getRotation()*180/M_PI);

    }

    zoom = 1;
    rotation = 0;
}

void GestionSFML::initWindow(int width, int height, string title)
{   //RenderWindow window(VideoMode(width,height),title); 
}

GestionSFML::~GestionSFML()
{   window.close();
    voitures.clear();
    obstacles.clear();
}

void GestionSFML::boucleJeuSFML()
{   sf::RenderWindow window(VideoMode(1280,720),"Vroum",Style::Fullscreen);
    //centre la vue sur (0,0) avec un carré de 640*360 px
    sf::Clock clock;
    clock.restart();
    
    sf::Font font;
    if (!font.loadFromFile("data/fonts/Papyrus.ttf")){
        cout << "Souci de police" << endl;
    }

    sf::Text text;

    // select the font
    text.setFont(font); // font is a sf::Font
    // set the character size
    text.setCharacterSize(20); // in pixels, not points!
    text.setScale(0.25,0.25);
    // set the color
    text.setFillColor(sf::Color::White);

    while (window.isOpen()){
    // On traite tous les évènements de la fenêtre qui ont été générés depuis la dernière itération de la boucle
        Event event;
        while (window.pollEvent(event)){

            // Partie physique
            //1-> on fait tout accélérer/tourner.
            if (event.type == Event::KeyPressed){
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
                    default:
                        break;
                }
            }
            //2-> on applique la résistance de l'air

            //3-> on teste les collisions




            //actualise position des voitures du jeu
            for (int i = 0; i < nb_voit; i++)
            {
                voitures[i].setPosition(tab_voit[i].getX(),tab_voit[i].getY());
                sprites[i].setPosition(tab_voit[i].getX(),tab_voit[i].getY());
                voitures[i].setRotation(tab_voit[i].getAngle()*180/M_PI);
                sprites[i].setRotation(tab_voit[i].getAngle()*180/M_PI);
            }
            
            // Fermeture de la fenêtre avec la croix (inutile pour le moment)
            if (event.type == Event::Closed){
                window.close();
            }

            text.setString("Vitesse : " + to_string(getVoiture(0).getVitesse()*3.6) + " km/h");
            
            
            // Clear en noir
            window.clear(Color::Black);
            text.setPosition(window.mapPixelToCoords(sf::Vector2i(10, 10)));
            
            
            window.draw(text);
            // On affiche le jeu
            afficherJeuSFML(window);
        }
  }
}


void GestionSFML::afficherJeuSFML(RenderWindow & window)
{   
    // Dessins
    for (int i = 0; i < nb_voit; i++)
    {
        window.draw(voitures[i]);
        window.draw(sprites[i]);
    }
    for (int i = 0; i < terrain.getNbProps(); i++)
    {
        window.draw(obstacles[i]);
    }
    
    // Affichage
    
    window.setView(sf::View(voitures[0].getPosition(), sf::Vector2f(320.f, 180.f)));
    window.display();

}

