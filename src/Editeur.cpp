#include "Editeur.h"

Editeur::Editeur()
{   centre = Vector2f(0,0);
    zoom = 10;
    interface.vue = View(Vector2f(0.f,0.f), Vector2f(1280.f/zoom, 720.f/zoom));
}

void map_pos_to_grid(Vecteur & pos)
{   if (pos.x > 0) pos.x = (int)pos.x - (int)pos.x % 7;
    else pos.x = (int)pos.x - (int)pos.x % 7 - 7;
    if (pos.y > 0) pos.y = (int)pos.y - (int)pos.y % 7;
    else pos.y = (int)pos.y - (int)pos.y % 7 -7;
}

void Editeur::boucleEditeur(RenderWindow & window, int volume)
{
    Music music;
    music.openFromFile("data/sounds/editeur.wav");
    music.setVolume(volume*4);
    music.setLoop(true);
    music.play();

    interface.loadRefProps();
    cout << "chargement des textures" << endl;
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
        afficherDebug(window, text);
        window.draw(text);

        window.display();

    } while (!quitter);
    music.stop();
}

bool Sauvegarder_Niveau_txtGlobal(string & path) {
    //on valide la demande
    Selection param;
    cout<<"Sauvegarder ? (y/n) : ";
    cin>>param.nom_circuit;
    if (param.nom_circuit != "y" && param.nom_circuit != "Y") return false;

    //on demande le nom que l'on veut donner au circuit
    cout<<"entrer nom du circuit : ";
    cin>>param.nom_circuit;   
    //on ouvre le fichier dans lequel on a le tableau des niveaux
    bool existe = true;
    if (get_parametre_circuit(param)) {// si le fichier existe déjà, on demande si on veut l'écraser
        cout<<"Ce nom est déjà pris, voulez vous l'écraser ? (y/n) : ";
        cin>>param.choix;
        if (param.choix != "y" && param.choix != "Y")
        {   cout<<"Sauvegarde annulée"<<endl;
            return false;//sortie de la fonction
        }
        
    }
    //sinon, on définit ainsi le chemin du fichier
    else {
        existe = false;
        param.chemin_circuit = "data/circuits/"+param.nom_circuit+".json";
    }

    
    
    //boucle de saisie du nombre de tours
    bool is_number=true;
    do {
        if(!is_number) cout << "ENTRER UN NOMBRE SUPERIEUR OU EGAL A 1 ! ";
        else cout << "entrer nombre de tours : ";
        is_number = true;
        cin >> param.choix;
        cout<<endl;
        //test si nb_tour est un nombre
        for (char c : param.choix) if (c < '0' || c > '9') {
            is_number = false;
        }
        if (param.choix.size() == 0) is_number = false;
        else if (param.choix.size() == 1) if (param.choix[0] == '0') is_number = false;
    } while (!is_number);
    param.nb_tours = stoi(param.choix);//on convertit le nombre de tours en int

    
    //on ouvre le fichier dans lequel on a le tableau des niveaux en lecture
    ifstream fichier1;
    fichier1.open("data/liste_niveaux.json");
    json liste_niveaux;
    fichier1 >> liste_niveaux;
    fichier1.close();

    // le même en écriture
    ofstream fichier;
    fichier.open("data/liste_niveaux.json");

    //on ajoute le nouveau niveau à la liste si il n'existe pas déjà
    if (!existe) liste_niveaux.push_back(json::object());
    unsigned int rang = param.indice_circuit;
    //dans tous les cas, on met à jour les informations du niveau
    liste_niveaux[rang]["nom"] = param.nom_circuit;
    liste_niveaux[rang]["path"] = param.chemin_circuit;
    liste_niveaux[rang]["nombreTour"] = param.nb_tours;

    //on sauvegarde la liste des niveaux
    fichier << liste_niveaux.dump(4);
    fichier.close();

    path = param.chemin_circuit;
    //si on arrive ici, c'est que la liste des niveaux a été mise à jour
    return true;//on retourne true pour indiquer qu'il faut sauvegarder le niveau en lui même
}

bool Selection_niveau(string & path) {
    //demande si on veut charger un nouveau circuit
    string nom;
    cout<<"Charger un nouveau circuit ? (y/n) : ";
    cin>>nom;

    if (nom!="y"&&nom!="Y") return false;

    //affiche la liste des circuits
    cout<<"Charger citcuit (nom) :";   
    ifstream fichier;
    fichier.open("data/liste_niveaux.json");
    json liste_niveaux;
    fichier >> liste_niveaux;
    fichier.close();
    cout<<endl;
    int i=0;
    for (auto niveau : liste_niveaux)
    {   cout<<i<<" : "<<niveau["nom"];
        cout<<" ( "<<niveau["nombreTour"]<<" tours )"<<endl;
        if (!niveau.contains("listeTemps")) cout<<"    Aucun temps enregistré"<<endl;
        else {
            cout<<"    Temps enregistrés :"<<endl;
            for (auto temps : niveau["listeTemps"])
            {   cout<<"    "<<temps["nom"]<<" : "<<temps["temps"]<<endl;
            }
        }
        i++;
    }
    //demande le nom du circuit à charger
    cout<<"entrer le nom du circuit :";
    cin>>nom;
    for (int i=0; i< (int)liste_niveaux.size(); i++) {
        
        if (liste_niveaux[i]["nom"] == nom) {
            path = liste_niveaux[i]["path"];
            //propose de supprimer le circuit
            cout<<"Supprimer le circuit ? (y/n) : ";
            cin >> nom;
            if (nom != "y" && nom != "Y") return true;//on retourne true pour indiquer qu'il faut charger le niveau en lui même
            cout<<"êtes vous sur ? (y/n) : ";
            cin >> nom;
            if (nom != "y" && nom != "Y") return false;//on ne charge pas le circuit
        

            std::remove(path.c_str());//si on a supprime le fichier, et on continue même si ça n'a pas marché
            //delete p_path;
            //on supprime le circuit de la liste
            liste_niveaux.erase(i);
            ofstream fichier2;
            fichier2.open("data/liste_niveaux.json");
            fichier2 << liste_niveaux.dump(4);
            fichier2.close();
            return false;//on ne charge pas le circuit
        }
    } //si on arrive ici, c'est que le circuit n'a pas été trouvé

    //si le circuit n'a pas été trouvé, on demande si on veut charger un lien custom
    cout<<"Entrer un lien vers un circuit non déclaré (à vos risques et périls) : ";
    cin>> path;
    
    //on vérifie le chemin
    if (path.find(".json") != path.size()-5)
    {   cout<<"Le fichier doit être au format json"<<endl;
        return false;
    }
    fichier.open(path);//on tente d'ouvrir le fichier en lecture
    bool good=true;
    if(!fichier.is_open()) {
        cout<<"Le fichier n'a pas pu être ouvert"<<endl;
        good = false;
    }
    else if (!fichier.good()) {
        cout<<"Le fichier a un problème"<<endl;
        good = false;
    }
    fichier.close();
    return good;
}

bool Editeur::gestionEvent(RenderWindow & window)
{   Event event;
    while(window.pollEvent(event))
    {   if (event.type == Event::Closed) return true;
        else if (event.type == Event::KeyPressed)
        {   if (event.key.code == Keyboard::Escape) return true;
            if (event.key.code == Keyboard::Z)
                deplacer_prop(0, -7);
            else if (event.key.code == Keyboard::S)
                deplacer_prop(0, 7);
            if (event.key.code == Keyboard::Q)
                deplacer_prop(-7, 0);
            else if (event.key.code == Keyboard::D)
                deplacer_prop(7, 0);
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
                    string path;
                    if (Sauvegarder_Niveau_txtGlobal(path)) sauvegarder(path);
                    window.setVisible(true);
                }
                else if (event.key.code == Keyboard::L)
                {   window.setVisible(false);
                    string path;
                    if (Selection_niveau(path)) charger(path);
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
                ajouter_prop(nouveau_prop,window.mapPixelToCoords(mouse_position) + Vector2f(7,7));

                ajout_prop = true;
            }
            else deplacer_vue = true;
        }
        if (deplacer_vue) deplacer(-delta.x, -delta.y);
        else if (ajout_prop)
        {   
            Vecteur true_new_pos(local_mouse_pos.x+7, local_mouse_pos.y+7);
            map_pos_to_grid(true_new_pos);
            //update de la position du dernier prop ajouté
            tab_props[prop_selectionne].setPos(true_new_pos);
            //update graphique
            interface.dernierProp().setPosition(true_new_pos.x, true_new_pos.y);
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
        Vecteur hitbox;
        for (int i = 0;i < nb_props; i++)
        {   switch (tab_props[i].getType())
            {
                case Tip::turn2:    hitbox = Vecteur(14,14);    break;
                case Tip::turn3:    hitbox = Vecteur(21,21);    break;
                case Tip::turn4:    hitbox = Vecteur(28,28);    break;
                default:            hitbox = Vecteur(7,7);      break;
            }
            tab_props[i].setHitbox(hitbox);
            interface.loadProp(tab_props[i]);
        }
        prop_selectionne = -1;
    }
    return succes;
}   

void Editeur::sauvegarder(string path)
{   
    ofstream fichier;
    fichier.open(path);
    
    json j;
    int i=0;
    int ordre=0;
    for (auto prop : tab_props) {
        
        j["Props"][i]["x"] = prop.getX();
        j["Props"][i]["y"] = prop.getY();
        j["Props"][i]["rotation"] = prop.getRotation();
        j["Props"][i]["Type"] = prop.getType();
        j["Props"][i]["l"] = prop.getLong();
        j["Props"][i]["L"] = prop.getLarg();
        if (prop.getType() == Tip::checkpoint) {
            //le ordre ième checkpoint est le i ème prop
            j["ordre_checkpoints"][ordre] = i;
            ordre++;
        }
        i++;
    }

    fichier << j.dump(4);
    fichier.close();
}

void Editeur::ajouter_prop(Tip t, Vector2f pos)
{   
    tab_props.push_back(Props());
    tab_props[nb_props].set_type(t);
    tab_props[nb_props].setPos(Vecteur(pos.x, pos.y));
    Vecteur hitbox;
    switch (tab_props[nb_props].getType())
    {
        case Tip::turn2:    hitbox = Vecteur(14,14);    break;
        case Tip::turn3:    hitbox = Vecteur(21,21);    break;
        case Tip::turn4:    hitbox = Vecteur(28,28);    break;
        default:            hitbox = Vecteur(7,7);      break;
    }
    tab_props[nb_props].setHitbox(hitbox);

    interface.loadProp(tab_props[nb_props]);
    nb_props++;
    prop_selectionne = nb_props-1;
    
    if (t == Tip::checkpoint) ordre_checkpoint.push_back(prop_selectionne);
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
    afficherDebug(window, text);
    interface.drawTerrain(window);
    window.setView(interface.vue);

    RectangleShape rectangle_selectionne(Vector2f(14,14));
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
    rectangle_selectionne.setOrigin(7,7);
    pos=tab_props[prop_selectionne].getPos();
    rectangle_selectionne.setPosition(pos.x,pos.y);
    window.draw(rectangle_selectionne);//celui selectionné

    interface.drawRefProps(window);
}