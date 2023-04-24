#include "Editeur.h"

Editeur::Editeur()
{   centre = Vector2f(0,0);
    zoom = 10;
    interface.vue = View(Vector2f(0.f,0.f), Vector2f(1280.f/zoom, 720.f/zoom));
}

void map_pos_to_grid(Vecteur & pos)
{   if (pos.x > 0) pos.x = (int)pos.x - (int)pos.x % 12;
    else pos.x = (int)pos.x - (int)pos.x % 12 - 12;
    if (pos.y > 0) pos.y = (int)pos.y - (int)pos.y % 12;
    else pos.y = (int)pos.y - (int)pos.y % 12 -12;
}

void Editeur::boucleEditeur(RenderWindow & window)
{   
    interface.loadRefProps();
    cout<<"chargement des textures"<<endl;
    window.setFramerateLimit(60);
    Font font;
    font.loadFromFile("data/fonts/Consolas.ttf");
    Text text;
     // select the font
    text.setFont(font); // font is a Font
    // set the character size
    text.setCharacterSize(50); // in pixels, not points!
    
    Vector2i pos_mouse_init;
    Vecteur depl_mouse;

    bool quitter = false;

    select_prop();
    select_prop(false);
    cout<<"boucle editeur"<<endl;
    do {
        //gestion des actions clavier et de ce qui en dépend + mollette souris
        if(gestionEvent(window)) quitter=true;

        //gestion des actions souris et de ce qui en dépend
        gestionSouris(window);
       

        lier_window(window);
        text.setScale(0.3/(float)zoom,0.3/(float)zoom);
        text.setString("Position : " + to_string(centre.x) + " , " + to_string(centre.y));
        Text balek;
        afficherDebug(window, text, balek);
        window.draw(text);

        window.display();

    } while (!quitter);
}

bool Editeur::gestionEvent(RenderWindow & window)
{   Event event;
    while(window.pollEvent(event))
    {   if (event.type == Event::Closed) return true;
        else if (event.type == Event::KeyPressed)
        {   if (event.key.code == Keyboard::Escape) return true;
            if (event.key.code == Keyboard::Z)
                deplacer_prop(0, -12);
            else if (event.key.code == Keyboard::S)
                deplacer_prop(0, 12);
            if (event.key.code == Keyboard::Q)
                deplacer_prop(-12, 0);
            else if (event.key.code == Keyboard::D)
                deplacer_prop(12, 0);
            if (event.key.code == Keyboard::R)
                rotate_prop();
            
            if (!ajout_prop && !deplacer_vue)
            {   if (event.key.code == Keyboard::A)
                    select_prop();
                else if (event.key.code == Keyboard::E)
                    select_prop(false);
                else if (event.key.code == Keyboard::G)
                    supprimer_prop();
                else if (event.key.code == Keyboard::C)
                {   window.setVisible(false);
                    cout<<"Sauvegarder ? (y/n) : ";
                    string nom;
                    cin>>nom;
                    if (nom == "y" || nom == "Y")
                    {   
                        string path = "data/circuits/";
                        ofstream fichier;
                        cout<<"entrer nom du circuit : ";
                        cin>>nom;
                        path += nom + ".json";
                        sauvegarder(path);
                    }
                    window.setVisible(true);
                }
                else if (event.key.code == Keyboard::L)
                {   window.setVisible(false);
                    string path;
                    cout<<"Charger un nouveau circuit ? (y/n) : ";
                    cin>>path;
                    if (path=="y"||path=="Y")
                    {
                        cout<<"Charger citcuit (nom) :";   
                        cin>>path;
                        path = "data/circuits/" + path + ".json";
                        charger(path);
                    }
                    window.setVisible(true);
                }
            }       
        }
        else if (event.type == sf::Event::MouseWheelScrolled)
        {   int delta = event.mouseWheelScroll.delta;
            zoom_(delta);
        }
    }
    return false;
}

void Editeur::gestionSouris(RenderWindow const & window)
{   //gestion des actions souris
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {   
        Vector2i mouse_position = Mouse::getPosition(window);
        Vector2f local_mouse_pos = window.mapPixelToCoords(mouse_position);
        const auto delta = 
                local_mouse_pos -
                window.mapPixelToCoords(mouse_prev_pos);

        if (!deplacer_vue && !ajout_prop)
        {   
            Tip nouveau_prop = interface.refPropSelected(window);
            if (nouveau_prop != Tip::nondef)
            {   
                ajouter_prop(nouveau_prop,window.mapPixelToCoords(mouse_position));

                ajout_prop = true;
            }
            else deplacer_vue = true;
        }
        if (deplacer_vue) deplacer(-delta.x, -delta.y);
        else if (ajout_prop)
        {   
            Vecteur true_new_pos(local_mouse_pos.x+12, local_mouse_pos.y);
            map_pos_to_grid(true_new_pos);
            //update de la position du dernier prop ajouté
            tab_props[prop_selectionne].setPos(true_new_pos);
            //update graphique
            interface.dernierProp().setPosition(true_new_pos.x-6, true_new_pos.y+6);
        }
    }
    else
    {   if (ajout_prop)
        {   //on supprime les autres props possédant la même position
            int autre_prop = getProp(tab_props[prop_selectionne].getPos());
            if (autre_prop != -1 && autre_prop != prop_selectionne && tab_props[prop_selectionne].getType() != checkpoint) supprimer_prop(autre_prop);
            ajout_prop = false;
        }
        deplacer_vue = false;
    }
    mouse_prev_pos = Mouse::getPosition(window);
}

void Editeur::rotate_prop(float angle)
{   if (prop_selectionne != -1)
    {   tab_props[prop_selectionne].setRot(tab_props[prop_selectionne].getRotation() + angle * M_PI / 180);
        interface.getProp(prop_selectionne).rotate(angle);
    }
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

void Editeur::deplacer_prop(float dx, float dy)
{   if (prop_selectionne != -1)
    {   Vecteur newpos = tab_props[prop_selectionne].getPos() + Vecteur(dx, dy);
        tab_props[prop_selectionne].setPos(newpos);
        interface.getProp(prop_selectionne).move(dx,dy);
    }
}

bool Editeur::charger(string path)
{   //charge le terrain en lui même
    bool succes = chargerJSON(path);
    //charrge les props
    if (succes)
    {   interface.clearProps();
        for (int i = 0;i < nb_props; i++) interface.loadProp(tab_props[i]);
        prop_selectionne = -1;
    }
    return succes;
}   

void Editeur::sauvegarder(string path)
{   ofstream fichier;
    fichier.open(path);
    
    json j;
    for (int i = 0; i < nb_props; i++)
    {   j["Props"][i]["x"] = tab_props[i].getX();
        j["Props"][i]["y"] = tab_props[i].getY();
        j["Props"][i]["rotation"] = tab_props[i].getRotation();
        j["Props"][i]["Type"] = tab_props[i].getType();
        j["Props"][i]["l"] = tab_props[i].getLong();
        j["Props"][i]["L"] = tab_props[i].getLarg();
    }

    fichier << j.dump(4);

    fichier.close();
}

void Editeur::ajouter_prop(Tip t, Vector2f pos)
{   
    tab_props.push_back(Props());
    tab_props[nb_props].set_type(t);
    tab_props[nb_props].setPos(Vecteur(pos.x+20, pos.y-6));
    interface.loadProp(tab_props[nb_props]);
    nb_props++;
    prop_selectionne = nb_props-1;
}

void Editeur::select_prop(bool plus_recent)
{   if (nb_props != 0)
    {   if (!plus_recent)
        {   prop_selectionne--;
            if(prop_selectionne < 0) prop_selectionne = nb_props-1;
        }
        else
        {   prop_selectionne++;
            if(prop_selectionne >= nb_props) prop_selectionne = 0;
        }
        Vecteur ctemp;
        ctemp=tab_props[prop_selectionne].getPos();
        centre.x = ctemp.x;
        centre.y = ctemp.y;
        interface.vue.setCenter(centre.x, centre.y);
    }
    else prop_selectionne = -1;
}

void Editeur::supprimer_prop(int i)
{   if (nb_props != 0)
    {   nb_props--;
        if (i == -1)
        {   tab_props.erase(tab_props.begin()+prop_selectionne);
            i=prop_selectionne;
        }
        else tab_props.erase(tab_props.begin()+i);
        
        interface.supprimerProp(i);
        select_prop(false);
    }
}

bool Editeur::test_regression()
{   charger();
    //Init_props();
    sauvegarder("data/circuit/test_regression.json");
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

    RectangleShape rectangle_selectionne(Vector2f(12,12));
    rectangle_selectionne.setOutlineColor(Color::Red);
    rectangle_selectionne.setFillColor(Color::Transparent);
    rectangle_selectionne.setOutlineThickness(0.3);
    //fait en sorte de lier le rectangle à la interface.vue
    Vector2f pos2 = window.mapPixelToCoords(Mouse::getPosition(window));
    Vecteur pos(pos2.x, pos2.y);
    map_pos_to_grid(pos);
    rectangle_selectionne.setPosition(pos.x, pos.y);
    window.draw(rectangle_selectionne);//celui de la souris
    rectangle_selectionne.setOutlineColor(Color::Blue);
    rectangle_selectionne.setOrigin(12,0);
    pos=tab_props[prop_selectionne].getPos();
    rectangle_selectionne.setPosition(pos.x,pos.y);
    window.draw(rectangle_selectionne);//celui selectionné

    interface.drawRefProps(window);
}

