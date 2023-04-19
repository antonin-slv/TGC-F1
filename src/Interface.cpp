#include "Interface.h"

Interface::Interface()
{
    //ctor
}

void Interface::loadTerrain(Terrain & terrain,string texture_path)
{
    Vecteur hitbox;
    Vecteur pos;
    for (int i = 0; i < terrain.getNbProps(); i++)
    {   hitbox=terrain.getProp(i).getHitbox()*2;
        props.push_back(RectangleShape(Vector2f(hitbox.x,hitbox.y)));
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
{  for (int i = 0; i < props.size(); i++) window.draw(props[i]);
}