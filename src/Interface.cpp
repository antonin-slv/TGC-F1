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

    text_voiture.loadFromFile("data/voitures/F1.png");
    cout<<"Cars loaded"<<endl;
    //ctor
}

void Interface::clearProps()
{   props.clear();
}

void afficherDebug(RenderWindow & window, Text & text)
{   
    // Dessins
    text.setPosition(window.mapPixelToCoords(Vector2i(10, 10)));
    
    window.draw(text);

}

void afficherDebug2(RenderWindow & window, Text & text)
{   
    // Dessins
    text.setPosition(window.mapPixelToCoords(Vector2i(window.getSize().x*0.82, 10)));
    
    window.draw(text);

}


Texture * Interface::getTexture(Tip type)
{   switch (type)
    {   case Tip::road:         return &road; 
        case Tip::road_kerb_a:  return &road_kerb_a;
        case Tip::road_kerb_m:  return &road_kerb_m;
        case Tip::road_kerb_z:  return &road_kerb_z;
        case Tip::turn1:        return &turn1;
        case Tip::turn2:        return &turn2;
        case Tip::turn3:        return &turn3;
        case Tip::turn4:        return &turn4;
        case Tip::grass:        return &grass;
        case Tip::finish:       return &finish;
        case Tip::checkpoint:   return &checkpoint;
        default:                return nullptr;
    }

}


void Interface::loadProp(Props const &  prop)
{   Texture * texture=getTexture(prop.getType());

    Sprite prop_(*texture);
    Vecteur taille(14.0/texture->getSize().x,14.0/texture->getSize().y);
    Vecteur origin(prop_.getLocalBounds().width/2,prop_.getLocalBounds().height/2);
    switch(prop.getType())
    {   case Tip::turn2:        
            taille = taille * 2;
            break;
        case Tip::turn3:
            taille = taille * 3; break;
        case Tip::turn4:
            taille = taille * 4;
            break;
        default:                break;
    }
    prop_.scale(taille.x,taille.y);
    
    prop_.setOrigin(origin.x,origin.y);
    
    Vecteur pos = prop.getPos();
    prop_.setPosition(pos.x,pos.y);
    prop_.setRotation(90+prop.getRotation()*180/M_PI);

    props.push_back(prop_);

}

void Interface::loadTerrain(Terrain & terrain,string texture_path)
{
    Vecteur hitbox;
    Vecteur pos;
    int i=0;
    for (auto & prop : terrain.getTabProps())
    {   if (prop.getType() != Tip::nondef)
        {      loadProp(prop);
                cout << "p" << i++ << " ";
        }
    }
    cout << endl << "Chargement terrain ok" << endl;
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
    voiture_.setHitbox(hitbox);
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
    if (ref_props.size()==0)
    {   

        for (int i=0;(Tip)i!=Tip::end_of_class;i++)
        {   
            Texture * texture=getTexture((Tip)i);
            if (texture!=nullptr)
            {   Sprite prop(*texture);
                
                Vecteur taille(85.0/texture->getSize().x,85.0/texture->getSize().y);
                //cout<<"local bounds... width : "<<prop.getLocalBounds().width<<", height :"<<prop.getLocalBounds().height<<endl;
                //cout<<"taille : "<<taille.x<<", "<<taille.y<<endl;
                prop.scale(taille.x,taille.y);
                prop.setPosition(10, 90*i);
                //prop.setOrigin(prop.getLocalBounds().width/2,prop.getLocalBounds().height/2);
                ref_props.push_back(prop);
            }
        }
    }
}

void Interface::drawRefProps(RenderWindow & window)
{   
    
    window.setView(window.getDefaultView());

    RectangleShape menu(Vector2f(105, window.getSize().y));
    menu.setFillColor(Color(200,150,110,200));
    menu.setPosition(0, 35);
    window.draw(menu);
    for (auto & prop : ref_props) window.draw(prop);

    window.setView(vue);
}

Tip Interface::refPropSelected(RenderWindow const & window)
{   Vector2i mouse_pos = Mouse::getPosition(window);
   
    if (mouse_pos.x<95 && mouse_pos.y>30 && mouse_pos.x>10)
    {   
        for (int i = 0; (Tip)i != Tip::end_of_class; i++)
        {   if ((Tip) i == Tip::nondef) continue;
            if (mouse_pos.y>90*i && mouse_pos.y<90*(i+1)-5) return Tip(i);
        }
    }
    return Tip::nondef;

}

Sprite & Interface::dernierProp()
{   return props[props.size()-1];
}

Sprite & Interface::getProp(int i)
{   return props[i];
}


void Interface::supprimerProp(int i)
{   if (i == -1) props.pop_back();
    else props.erase(props.begin()+i);
}
