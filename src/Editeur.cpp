#include "Editeur.h"



Editeur::Editeur()
{   centre = Vecteur(0,0);
    zoom = 1;
    vue = View(Vector2f(0.f,0.f), Vector2f(1280.f/zoom, 720.f/zoom));
}

void Editeur::boucleEditeur(RenderWindow & window)
{   window.setFramerateLimit(60);
    do {
        Event event;
        while (window.pollEvent(event))
        {   if (event.type == Event::Closed) return;
            if (event.type == Event::KeyPressed)
            {   if (event.key.code == Keyboard::Escape) return;
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
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {   Vector2i posf = Mouse::getPosition(window);

            centre.x = -posf.x/2-vue.getCenter().x;
            centre.y = -posf.y/2-vue.getCenter().y;
            vue.setCenter(centre.x, centre.y);
        }
        //on fait en sorte de pouvoir zoomer en tournant la roue de la molette

        lier_window(window);
        Text text;
        text.setString("Position : " + to_string(centre.x) + " , " + to_string(centre.y));
        Text balek;
        afficherDebug(window, text,balek);
        window.draw(text);
        window.draw(RectangleShape(Vector2f(1,1)));
        window.display();


    } while (true);

}

void Editeur::zoom_(float zoom_)
{   zoom += zoom_;
    if (zoom < 0.1) zoom = 0.1;
    vue.setSize(Vector2f(1280.f/zoom, 720.f/zoom));
}

void Editeur::deplacer(float dx, float dy)
{
    centre.x += dx;
    centre.y += dy;
    vue.move(dx, dy);
}

bool Editeur::charger(string path)
{   //charge le terrain en lui même
    bool succes = chargerJSON(path);
    //charrge les props
    if (succes)
    {  for (int i = 0;i < nb_props; i++)
        {   interface.loadProp(tab_props[i],"");
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

void Editeur::Init_props()
{   int i=0;
    while (i++ != Tip::end_of_class)
    {   ref_props.push_back(Props());
        ref_props[i].prop_set_type((Tip) i);
    }
    //TODO
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
        vue.setCenter(centre.x, centre.y);
    }
}

void Editeur::supprimer_props()
{   //tab_props.erase(prop_selectionne);
    nb_props--;
    prop_selectionne--;
}

bool Editeur::test_regression()
{   charger();
    Init_props();
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
    window.setView(vue);

}

