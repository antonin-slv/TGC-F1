#include "Editeur.h"



Editeur::Editeur()
{   centre = Vecteur(0,0);
    zoom = 10;
    interface.vue = View(Vector2f(0.f,0.f), Vector2f(1280.f/zoom, 720.f/zoom));
}

void Editeur::boucleEditeur(RenderWindow & window)
{   
    interface.loadRefProps();
    
    window.setFramerateLimit(60);
    Font font;
    font.loadFromFile("data/fonts/Consolas.ttf");
    Text text;
     // select the font
    text.setFont(font); // font is a Font
    // set the character size
    text.setCharacterSize(50); // in pixels, not points!
    bool deplacer_vue = false;
    Vector2i pos_mouse_init;
    Vecteur depl_mouse;

    bool quitter = false;
    do {
        
        Event event;
        while (window.pollEvent(event))
        {   if (event.type == Event::Closed) quitter = true;
            if (event.type == Event::KeyPressed)
            {   if (event.key.code == Keyboard::Escape) quitter = true;
                if (event.key.code == Keyboard::Z)
                    deplacer(0, -100/zoom);
                if (event.key.code == Keyboard::S)
                    deplacer(0, 100/zoom);
                if (event.key.code == Keyboard::Q)
                    deplacer(-100/zoom, 0);
                if (event.key.code == Keyboard::D)
                    deplacer(100/zoom, 0);
                if (event.key.code == Keyboard::A)
                    select_prop();        
                /*
                if (event.key.code == Keyboard::E)
                    ajouter_prop();
                if (event.key.code == Keyboard::R)
                    supprimer_props();
                */
            }
            if (event.type == sf::Event::MouseWheelScrolled)
            {   int delta = event.mouseWheelScroll.delta;
                zoom_(delta);
            }
        }
        //déplacement de la caméra
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {   if (!deplacer_vue)
            {   pos_mouse_init = Mouse::getPosition(window);
                deplacer_vue = true;
            }
            Vector2i posf = Mouse::getPosition(window);
            depl_mouse = Vecteur(posf.x-pos_mouse_init.x, posf.y-pos_mouse_init.y);
            depl_mouse = depl_mouse * (-1/(float)zoom);
            interface.vue.setCenter(depl_mouse.x+centre.x,depl_mouse.y+centre.y);
        }
        else
        {   deplacer_vue = false;
            centre= depl_mouse+centre;
            depl_mouse = Vecteur(0,0);
        }



        lier_window(window);
        text.setScale(0.3/(float)zoom,0.3/(float)zoom);
        text.setString("Position : " + to_string(centre.x) + " , " + to_string(centre.y));
        Text balek;
        afficherDebug(window, text, balek);
        window.draw(text);
        window.draw(RectangleShape(Vector2f(1,1)));


        window.display();


    } while (!quitter);

}

void Editeur::zoom_(float zoom_)
{   zoom += zoom_;
    if (zoom < 1) zoom = 1;
    interface.vue.setSize(Vector2f(1280.f/zoom, 720.f/zoom));
}

void Editeur::deplacer(float dx, float dy)
{
    centre.x += dx;
    centre.y += dy;
    interface.vue.move(dx, dy);
}

bool Editeur::charger(string path)
{   //charge le terrain en lui même
    bool succes = chargerJSON(path);
    //charrge les props
    if (succes)
    {  for (int i = 0;i < nb_props; i++)
        {   interface.loadProp(tab_props[i]);
        }
    }
    return succes;
}   

void Editeur::sauvegarder()
{   string path = "data/circuits/test1.json";

    ofstream fichier;

    json j;
    for (int i = 0; i < nb_props; i++)
    {   j["props"][i]["x"] = tab_props[i].getX();
        j["props"][i]["y"] = tab_props[i].getY();
        j["props"][i]["rotation"] = tab_props[i].getRotation();
        j["props"][i]["type"] = tab_props[i].getType();
        j["props"][i]["l"] = tab_props[i].getLong();
        j["props"][i]["L"] = tab_props[i].getLarg();
    }

    fichier.open(path);

    fichier << j.dump(4);

    fichier.close();
}

void Editeur::Init_ref_props()
{   int i=0;
    while (i++ != Tip::end_of_class)
    {   ref_props.push_back(Props());
        ref_props[i].prop_set_type((Tip) i);
    }
    
}


void Editeur::ajouter_prop(Tip t)
{   tab_props.push_back(ref_props[t]);
    nb_props++;
    prop_selectionne = nb_props-1;
    //TODO
}

void Editeur::select_prop()
{   if (nb_props != 0)
    {
        prop_selectionne++;
        if(prop_selectionne >= nb_props) prop_selectionne = 0;
        centre=tab_props[prop_selectionne].getPos();
        interface.vue.setCenter(centre.x, centre.y);
    }
}

void Editeur::supprimer_props()
{   tab_props.erase(tab_props.begin()+prop_selectionne);
    nb_props--;
    select_prop();
}

bool Editeur::test_regression()
{   charger();
    //Init_props();
    sauvegarder();
    //TODO
    return true;
}

void Editeur::lier_window(RenderWindow & window)
{  
    Text text;
    text.setString("Position : " + to_string(centre.x) + " , " + to_string(centre.y));
    Text balek;
     window.clear(Color::Black);
    afficherDebug(window, text,balek);
    interface.drawTerrain(window);
    window.setView(interface.vue);
    interface.drawRefProps(window);

}

