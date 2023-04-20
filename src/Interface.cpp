#include "Interface.h"
#include "Editeur.h"
#include "Jeu.h"
Interface::Interface()
{   finish.loadFromFile("data/props/finish.png");
    grass.loadFromFile("data/props/grass.png");
    road.loadFromFile("data/props/road.png");
    turn1.loadFromFile("data/props/turn1.png");
    //ctor
}

void afficherDebug(RenderWindow & window, Text & text, Text & texte_chrono)
{   
    // Dessins
    text.setPosition(window.mapPixelToCoords(Vector2i(10, 10)));
    texte_chrono.setPosition(window.mapPixelToCoords(Vector2i(1750, 10)));
    
    window.draw(text);
    window.draw(texte_chrono);

}

void Interface::loadProp(Props & prop)
{   
    Vecteur hitbox=prop.getHitbox();
    props.push_back(Sprite(road));
    props[props.size()-1].setColor(Color(255,255,255,255));
    props[props.size()-1].setScale(hitbox.x,hitbox.y);
    props[props.size()-1].setOrigin(hitbox.x/2,hitbox.y/2);
    Vecteur pos = prop.getPos();
    props[props.size()-1].setPosition(pos.x,pos.y);
    props[props.size()-1].setRotation(90+prop.getRotation()*180/M_PI);
}

void Interface::loadTerrain(Terrain & terrain,string texture_path)
{
    Vecteur hitbox;
    Vecteur pos;

    for (int i = 0; i < terrain.getNbProps(); i++)
    {   hitbox=terrain.getProp(i).getHitbox()*2;
        props.push_back(Sprite(road));
        props[i].setColor(Color(255,255,255,255));
        props[i].setScale(hitbox.x,hitbox.y);
        hitbox.x=hitbox.x/2;
        hitbox.y=hitbox.y/2;
        props[i].setOrigin(hitbox.x,hitbox.y);

        pos=terrain.getProp(i).getPos();
        props[i].setPosition(pos.x,pos.y);
        props[i].setRotation(90+terrain.getProp(i).getRotation()*180/M_PI);
        cout << "props ok" << endl;
    }
}

 void Interface::loadVoiture(Voiture & voiture_, string texture_path)
 {  //génération de sprite
    if(!text_voiture.loadFromFile(texture_path)){
        cout << "Problème de chargement de texture" << endl;
    }
    text_voiture.setSmooth(true);
    Vecteur taille(text_voiture.getSize().x,text_voiture.getSize().y);
    float proportion = taille.y/taille.x;
    //voiture.setScale(taille.x,taille.y);

    //taille=Vecteur(1/taille.y,1/taille.y);
    
    Vecteur hitbox(1.25*proportion,1.25);
    voiture.setTexture(text_voiture);
    voiture.scale(2.2*hitbox.y/taille.x,2.2*hitbox.y/taille.x);//inversés par rapport au reste...
    voiture.setOrigin(text_voiture.getSize().x/2,text_voiture.getSize().y/2);
    
    //ajoute une voiture de la classe voiture
    voiture_=Voiture(Moteur(),Roues(),796,0.14,hitbox.x,hitbox.y,0,0,0,0,0);
    cout<<"Hitbox : "<<hitbox.x<<" "<<hitbox.y<<endl;
    cout<<"Scale : "<<voiture.getLocalBounds().width<<" "<<voiture.getLocalBounds().height<<endl;
    cout << "Chargement voiture ok" << endl;
    
 }

 void Interface::drawVoiture(RenderWindow & window, Voiture & voiture_)
 {  voiture.setPosition(voiture_.getPos().x,voiture_.getPos().y);
    voiture.setRotation(-90+voiture_.getAngle()*180/M_PI);
    window.draw(voiture);
    

 }
 void Interface::drawVoitureHitbox(RenderWindow & window, Voiture & voiture_)
 {  RectangleShape hit_box(Vector2f(voiture_.getHitbox().x*2, voiture_.getHitbox().y*2));
    hit_box.setOrigin(voiture_.getHitbox().x, voiture_.getHitbox().y);
    hit_box.setRotation(voiture_.getAngle()*180/M_PI);
    hit_box.setFillColor(Color(255,0,0,150));
    //RectangleShape hit_box(Vector2f(10,10));
    hit_box.setPosition(voiture_.getPos().x,voiture_.getPos().y);
    window.draw(hit_box);
 }
 

void Interface::drawTerrain(RenderWindow & window)
{  for (long unsigned int i = 0; i < props.size(); i++) window.draw(props[i]);
}