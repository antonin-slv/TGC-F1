#include "GestionaireSFML.h"

#include <iostream>

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
        voitures[i].setRotation(getVoiture(i).getAngle());
    }

    for (int i = 0; i < terrain.getNbProps(); i++)
    {
        obstacles.push_back(RectangleShape(Vector2f(terrain.getProp(i).getLong(),terrain.getProp(i).getLarg())));
        obstacles[i].setFillColor(Color(0,0,255));
        obstacles[i].setPosition(terrain.getProp(i).getX(),terrain.getProp(i).getY());
        obstacles[i].setRotation(terrain.getProp(i).getRotation());
    }

    zoom = 1;
    centre = Vecteur(0, 0);
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

    window.setView(sf::View(sf::Vector2f(0.f, 0.f), sf::Vector2f(640.f, 360.f)));
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
        else update(' ');
        

        //actualise position des voitures du jeu
        for (int i = 0; i < nb_voit; i++)
        {
            voitures[i].setPosition(tab_voit[i].getX(),tab_voit[i].getY());
            voitures[i].setRotation(tab_voit[i].getAngle());
        }
        
        // Fermeture de la fenêtre avec la croix (inutile pour le moment)
        if (event.type == Event::Closed){
            window.close();
        }

        // Clear en noir
        window.clear(Color::Black);

        // Dessins
        for (int i = 0; i < nb_voit; i++)
        {
            window.draw(voitures[i]);
        }
        for (int i = 0; i < terrain.getNbProps(); i++)
        {
            window.draw(obstacles[i]);
        }

        if(Keyboard::isKeyPressed(Keyboard::Q)){
            window.close();
        }
        // Affichage
        window.display();
    }
  }
}
