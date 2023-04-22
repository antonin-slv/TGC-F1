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
    bool ajout_prop = false;

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
        //gestion des actions souris
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {   
            if (!deplacer_vue && !ajout_prop)
            {   Tip nouveau_prop = interface.refPropSelected(window);
                pos_mouse_init = Mouse::getPosition(window);
                
                if (nouveau_prop != Tip::nondef)
                {   ajouter_prop(nouveau_prop);
                    ajout_prop = true;
                }
                else
                {   
                    deplacer_vue = true;
                }

            }
            Vector2i posf = Mouse::getPosition(window);
            depl_mouse = Vecteur(posf.x-pos_mouse_init.x, posf.y-pos_mouse_init.y);
            depl_mouse = depl_mouse * (-1/(float)zoom);
            if (deplacer_vue) interface.vue.setCenter(depl_mouse.x+centre.x,depl_mouse.y+centre.y);
            else if (ajout_prop)
            {   Vecteur new_pos= depl_mouse * -1;
                new_pos.x += pos_mouse_init.x;
                new_pos.y += pos_mouse_init.y;
                //update de la position du dernier prop ajouté
                tab_props[prop_selectionne].setPos(new_pos);
                //update graphique
                interface.dernierProp().setPosition(new_pos.x, new_pos.y);
            }
        }
        else
        {   deplacer_vue = false;
            
            if (!ajout_prop) centre= depl_mouse+centre;
            ajout_prop = false;
            depl_mouse = Vecteur(0,0);
        }



        lier_window(window);
        text.setScale(0.3/(float)zoom,0.3/(float)zoom);
        text.setString("Position : " + to_string(centre.x) + " , " + to_string(centre.y));
        Text balek;
        afficherDebug(window, text, balek);
        window.draw(text);
        window.draw(RectangleShape(Vector2f(1,1)));
        RectangleShape rectangle_selectionne(Vector2f(12,12));
        rectangle_selectionne.setOutlineColor(Color::Red);
        rectangle_selectionne.setFillColor(Color::Transparent);
        rectangle_selectionne.setOutlineThickness(0.3);
        //fait en sorte de lier le rectangle à la vue
        Vector2f pos = window.mapPixelToCoords(Mouse::getPosition(window));
        if (pos.x > 0) pos.x = (int)pos.x - (int)pos.x % 12;
        else pos.x = (int)pos.x - (int)pos.x % 12 - 12;
        if (pos.y > 0) pos.y = (int)pos.y - (int)pos.y % 12;
        else pos.y = (int)pos.y - (int)pos.y % 12 -12;

        rectangle_selectionne.setPosition(pos.x, pos.y);
        window.draw(rectangle_selectionne);
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

void Editeur::ajouter_prop(Tip t)
{   
    tab_props.push_back(Props());
    tab_props[nb_props].set_type(t);
    nb_props++;
    prop_selectionne = nb_props-1;
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

