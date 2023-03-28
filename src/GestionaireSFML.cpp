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

    for (int i = 0; i < nb_voit; i++)
    {
        voitures.push_back(RectangleShape(Vector2f(getVoiture(i).getLongueur(),getVoiture(i).getLargeur())));
        voitures[i].setFillColor(Color(255,0,0));
        voitures[i].setPosition(getVoiture(i).getX(),getVoiture(i).getY());
        voitures[i].setRotation(getVoiture(i).getAngle()*180/M_PI);
    }

    for (int i = 0; i < terrain.getNbProps(); i++)
    {
        obstacles.push_back(RectangleShape(Vector2f(terrain.getProp(i).getLong(),terrain.getProp(i).getLarg())));
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
        if(Keyboard::isKeyPressed(Keyboard::O)){
            update('o');
        }
        else if(Keyboard::isKeyPressed(Keyboard::K)){
            update('k');
        }
        else if(Keyboard::isKeyPressed(Keyboard::L)){
            update('l');
        }
        else if(Keyboard::isKeyPressed(Keyboard::M)){
            update('m');
        }
        else
        {   update(' ');
            //cout<<"ralenti"<<clock.getElapsedTime().asSeconds()<<endl;
        }

        //actualise position des voitures du jeu
        for (int i = 0; i < nb_voit; i++)
        {
            voitures[i].setPosition(tab_voit[i].getX(),tab_voit[i].getY());
            voitures[i].setRotation(tab_voit[i].getAngle()*180/M_PI);
        }
        
        // Fermeture de la fenêtre avec la croix (inutile pour le moment)
        if (event.type == Event::Closed){
            window.close();
        }
         if(Keyboard::isKeyPressed(Keyboard::Q)){
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


void GestionSFML::afficherJeuSFML(sf::RenderWindow & window)
{   
    // Dessins
    for (int i = 0; i < nb_voit; i++)
    {
        window.draw(voitures[i]);
    }
    for (int i = 0; i < terrain.getNbProps(); i++)
    {
        window.draw(obstacles[i]);
    }
    
    // Affichage
    
    window.setView(sf::View(voitures[0].getPosition(), sf::Vector2f(320.f, 180.f)));
    window.display();

}

