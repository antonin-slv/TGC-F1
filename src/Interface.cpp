#include "Interface.h"
#include "Editeur.h"
#include "Jeu.h"
Interface::Interface()
{   finish.loadFromFile("data/props/finish.png");
    grass.loadFromFile("data/props/grass.png");
    checkpoint.loadFromFile("data/props/checkpoint.png");

    cout<<"base props loaded"<<endl;

    road.loadFromFile("data/props/road.png");
    road_kerb_a.loadFromFile("data/props/road_kerb_a.png");
    road_kerb_m.loadFromFile("data/props/road_kerb_m.png");
    road_kerb_z.loadFromFile("data/props/road_kerb_z.png");

    cout<<"roads loaded"<<endl;

    turn1.loadFromFile("data/props/turn1.png");
    turn2.loadFromFile("data/props/turn2.png");
    turn3.loadFromFile("data/props/turn3.png");
    turn4.loadFromFile("data/props/turn4.png");

    cout<<"Interface loaded"<<endl;

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

void Interface::loadProp(Props const &  prop)
{   switch (prop.getType())
    {   case Tip::road:
            props.push_back(Sprite(road));
            break;
        case Tip::road_kerb_a:
            props.push_back(Sprite(road_kerb_a));
            break;
        case Tip::road_kerb_m:
            props.push_back(Sprite(road_kerb_m));
            break;
        case Tip::road_kerb_z:
            props.push_back(Sprite(road_kerb_z));
            break;
        case Tip::turn1:
            props.push_back(Sprite(turn1));
            break;
        case Tip::turn2:
            props.push_back(Sprite(turn2));
            break;
        case Tip::turn3:
            props.push_back(Sprite(turn3));
            break;
        case Tip::turn4:
            props.push_back(Sprite(turn4));
            break;
        case Tip::grass:
            props.push_back(Sprite(grass));
            break;
        case Tip::finish:
            props.push_back(Sprite(finish));
            break;
        case Tip::checkpoint:
            props.push_back(Sprite(checkpoint));
            break;
        default:
            break;
    }

    Vecteur taille(2.2/road.getSize().x,2.2/road.getSize().y);
    props[props.size()-1].scale(taille.x,taille.y);
    
    props[props.size()-1].setOrigin(1.1,1.1);
    
    Vecteur pos = prop.getPos();
    props[props.size()-1].setPosition(pos.x,pos.y);
    props[props.size()-1].setRotation(90+prop.getRotation()*180/M_PI);
}

void Interface::loadTerrain(Terrain & terrain,string texture_path)
{
    Vecteur hitbox;
    Vecteur pos;
    int i=0;
    for (auto & prop : terrain.getTabProps())
    {   cout<<"Prop "<<i<<" aff ok"<<endl;
        loadProp(prop);
    }
    cout << "Chargement terrain ok" << endl;
}

 void Interface::loadVoiture(Voiture & voiture_, string texture_path)
 {  Vecteur taille(text_voiture.getSize().x,text_voiture.getSize().y);
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


void Interface::loadRefProps()
{   
    ref_props.push_back(Sprite(finish));
    ref_props.push_back(Sprite(grass));
    ref_props.push_back(Sprite(checkpoint));
    ref_props.push_back(Sprite(road));
    ref_props.push_back(Sprite(road_kerb_a));
    ref_props.push_back(Sprite(road_kerb_m));
    ref_props.push_back(Sprite(road_kerb_z));
    ref_props.push_back(Sprite(turn1));
    ref_props.push_back(Sprite(turn2));
    ref_props.push_back(Sprite(turn3));
    ref_props.push_back(Sprite(turn4));
    ref_props.push_back(Sprite(text_voiture));
    for (auto & prop : ref_props)
    {   prop.scale(0.1,0.1);
        prop.setOrigin(prop.getLocalBounds().width/2,prop.getLocalBounds().height/2);
    }

}

void Interface::drawRefProps(RenderWindow & window)
{   int i = 0;
    RectangleShape menu(Vector2f(100, 1000));
    menu.setFillColor(Color(20,0,0,150));
    menu.setPosition(window.mapPixelToCoords(Vector2i(0, 0)));
    window.draw(menu);
    for (auto & prop : ref_props)
    {   prop.setPosition(window.mapPixelToCoords(Vector2i(10, 10+50*i)));
        window.draw(prop);
        i++;
    }
}