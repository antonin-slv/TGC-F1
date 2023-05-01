#include "GestionaireSFML.h"

#include <iostream>
#include <math.h>
using namespace std;
using namespace sf;

GestionSFML::GestionSFML() {       
}

void GestionSFML::chargerNiveau(string path, int nb_tours) {
    
    ChargerTerrain(path,nb_tours);//réinitialise le jeu en Entier, et charge le terrain    
    interface.clearProps();//les props de l'interface, mais garde ses textures
    interface.loadTerrain(terrain,"data/props/road.png");//charge le terrain dans l'interface (2e argument : inutlie pour le moment)


    tab_voit.clear();//on supprime les voitures du jeu
    //on crée une voiture temporaire pour l'interface et on la charge dans l'interface et le jeu
    Voiture Voit_temp = Voiture(Moteur(),Roues(),796,0.14,0,0,0,0,0,0,0);
    Voit_temp.setRotation(terrain.getLigneArrivee().getRotation()+M_PI/2);
    Voit_temp.setPos(terrain.getLigneArrivee().getPos());
    cout<<"position voiture :"<<Voit_temp.getPos().x<<" "<<Voit_temp.getPos().y<<endl;
    interface.clearVoitures();//on supprime les voitures de l'interface
    interface.loadVoiture(Voit_temp,"data/cars/F1.png");//attribue une hitbox à la voiture et la charge dans l'interface
    ajouterVoiture(Voit_temp);
}


GestionSFML::~GestionSFML() {
    tab_voit.clear();
    cout<<"fin destruction gestionnaire"<<endl;
}

string affiche_temps(float t) {
    int minutes = floor(t/60);
    t-=minutes*60;
    int secondes = floor(t);
    t-=secondes;
    return to_string(minutes) + "\'" + to_string(secondes) + "\"" + to_string(int(t*1000));
}

//fonction qu'on appelle dans la boucle de jeu
bool GestionSFML::demarageJeuSFML(RenderWindow & window) {
    
    float temps_attente = 3.0f;
    
    Clock temps;//temps depuis le début du démarage du jeu
    temps.restart();
    
    string timer;
    Font font;
    font.loadFromFile("data/fonts/Consolas.ttf");
    Text texte_sf;
    initTexteCentre(window,texte_sf, font, 50,"", 150);
    
    do {
        Event event;
        while (window.pollEvent(event)) {
            //actions hors jeu ("globales"")
            if (event.type == Event::KeyPressed){
                switch (event.key.code){
                    case Keyboard::Escape :
                        return false;
                    case Keyboard::A :
                        return false;
                    default:
                        break;
                }
            }          
        }
        //on affiche le jeu
        afficherJeuSFML(window);

        //on affiche le temps d'attente
        window.setView(window.getDefaultView());
        timer = affiche_temps(temps_attente-temps.getElapsedTime().asSeconds());
        initTexteCentre(window,texte_sf, font, 50,timer.substr(2,4), 150);
        window.draw(texte_sf);
        //on prépare la caméra pour afficher le circuit
        View vue(interface.voiture.getPosition(), Vector2f(128.f, 72.f));
        window.setView(vue);
        window.display();
    } while (temps.getElapsedTime().asSeconds() < temps_attente);
    return true;
}


Time GestionSFML::boucleJeuSFML(RenderWindow & window, Clock & temps_au_tour, float decalage) {
    Font font;//charge la police
    font.loadFromFile("data/fonts/Consolas.ttf");

    Text text;//text pour le coin en haut à gauche (affiché par une fct de l'interface)
    text.setFont(font);
    text.setScale(0.025,0.025);

    cout << "debut ok" << endl;
    

    Text texte_temps_au_tour;//texte paramétré pour afficher le temps au tour
    texte_temps_au_tour.setFont(font);
    texte_temps_au_tour.setScale(0.025,0.025);

    Text vitesse;
    vitesse.setFont(font);
    vitesse.setScale(0.025,0.025);

    bool quitter = false;
    bool gagne = false;

    Color couleur_bouton(255,30,5,200);
    RectangleShape VICTOIRE;
    initBoutonCentre(window, VICTOIRE, 100, 600, 100);
    VICTOIRE.setFillColor(couleur_bouton);//carré dans lequel on écrit "VICTOIRE"
    Text texteVictoire;
    initTexteCentre(window, texteVictoire, font, 50, "VICTOIRE", 100);//texte "VICTOIRE" avec le même centre que le rectangle

    Text texteTempsCircuit;
    initTexteCentre(window, texteTempsCircuit, font, 40, "", 200);//écrit le temps du circuit si on setString

    Text infos_sorties;//info sur comment sortir du jeu
    initTexteCentre(window, infos_sorties, font, 30, "Appuyez sur A pour quitter", 250);
    infos_sorties.setFillColor(Color::White);
    //fin écran de fin

    if (!demarageJeuSFML(window)) {   
        cout<<"Jeu arrêté avant d'avoir commencé"<<endl;
        return seconds(-1);
    }
    //window.setVisible(true);//évite que le démarage ne cache la fenêtre par inadvertance

    ActionClavier action;//action à effectuer par le joueur

    long int nb_frames = 0;
    float temps = 0;
    Time temps_circuit = seconds(0);
    
    //on démarre les chrono
    Clock clock;//temps réel de la boucle
    clock.restart();
    
    Clock frames;//utilisée pour calculer le temps entre deux frames
    temps_au_tour.restart();//chrono qui mesure le temps au tour

    do {
    // On traite tous les évènements de la fenêtre qui ont été générés depuis la dernière itération de la boucle
        //cout<<"debut boucle";
        Event event;
        nb_frames++;
        temps+=frame_time;
        frame_time=frames.restart().asSeconds();
        while (window.pollEvent(event)){
            //actions hors jeu ("globales"")
            if (event.type == Event::KeyPressed){

                switch (event.key.code){
                    case Keyboard::Escape :
                        quitter = true;
                        break;
                    case Keyboard::A :
                        quitter = true;
                        break;
                    default:
                        break;
                }
            }
            //actions dans le jeu
            getActionClavier(event, action);            
        }

        //fait tout le bouleau d'update du jeu
        int rslt = update(action);
        if (!gagne)
        {
            if (rslt == -1) temps_circuit += temps_au_tour.restart();
            else if (rslt == 1)
            {   temps_circuit += temps_au_tour.restart();
                gagne = true;
            }
        }
        
        // Fermeture de la fenêtre avec la croix (inutile pour le moment)
        if (event.type == Event::Closed){
            window.close();
        }
        string affichage;
        
        
        //actualise position des voitures du jeu pour le texte ET L'OFFSET DE LA VUE !!!
        Voiture & voit = getVoiture(0);
        if (!gagne){
            affichage = "Tour " + to_string(nb_tour+1) + " / " +to_string(nb_tour_max) + "\n" +
                        "Checkpoint " + to_string(num_checkpoint) + " / " + to_string(terrain.getOrdreCheckpoint().size());
            texte_temps_au_tour.setString("Temps ce tour : "+affiche_temps(temps_au_tour.getElapsedTime().asSeconds()));
            vitesse.setString(to_string(int(voit.getVitesse()*3.6))+" km/h");
            float v = abs(voit.getVitesse()*3.6);
            if(v>255) v=255;
            vitesse.setFillColor(Color(255, sqrt(255*255-v*v), 255-v));
        }
        else{
            affichage = "Victoire ! \nTemps : " + to_string(temps_circuit.asSeconds()) + "\n";
            texte_temps_au_tour.setString("");
            vitesse.setString("");
        }
        
        text.setString(affichage);
        
        // On affiche le jeu
        afficherJeuSFML(window);
        if (gagne)
        {   window.setView(window.getDefaultView());
            window.draw(VICTOIRE);
            window.draw(texteVictoire);
            Text & TTT=texteTempsCircuit;
            TTT.setString("Temps total : "+affiche_temps(temps_circuit.asSeconds()));
            TTT.setPosition((window.getSize().x-TTT.getLocalBounds().width)/2, TTT.getPosition().y);

            window.draw(TTT);
            window.draw(infos_sorties);
        }
        View vue(interface.voiture.getPosition(), Vector2f(128.f, 72.f));
        vue.move(cos(voit.getAngle()) * voit.getVitesse() * decalage/24 ,decalage/24 * sin(voit.getAngle())*voit.getVitesse());
        window.setView(vue);
        afficherDebug(window, text, 75, 0.01, 0.01);
        afficherDebug(window, texte_temps_au_tour, 75, 0.8, 0.01);
        afficherDebug(window, vitesse, 200, 0.8, 0.8);
        window.display();
    } while (!quitter);
    if (gagne) return temps_circuit;
    else return seconds(-1);
}

void GestionSFML::afficherJeuSFML(RenderWindow & window) {   
    window.clear(Color(0,200,0));
    interface.drawTerrain(window);

    /*
    RectangleShape line(Vector2f(tab_voit[0].getVitesse()/2.2/1.25, 0.5));
    line.setPosition(tab_voit[0].getPos().x, tab_voit[0].getPos().y);
    line.rotate(tab_voit[0].getAngle()*180/M_PI);
    window.draw(line);
    */

    //interface.drawVoitureHitbox(window,tab_voit[0]);
    interface.drawVoiture(window, tab_voit[0]);
}

void getActionClavier(Event event, ActionClavier & action) {
    if (event.type == Event::KeyPressed){
        switch (event.key.code) {
            case Keyboard::Z :
                action.accelere=true;
                break;
            case Keyboard::S :
                action.freine=true;
                break;
            case Keyboard::Q :
                action.gauche=true;
                break;
            case Keyboard::D :
                action.droite=true;
                break;
            case Keyboard::Up :
                action.accelere=true;
                break;
            case Keyboard::Down :
                action.freine=true;
                break;
            case Keyboard::Left :
                action.gauche=true;
                break;
            case Keyboard::Right :
                action.droite=true;
                break;
            default:
                break;
        }
    }
    else if (event.type == Event::KeyReleased) {
        switch (event.key.code){
            case Keyboard::Z :
                action.accelere=false;
                break;
            case Keyboard::S :
                action.freine=false;
                break;
            case Keyboard::Q :
                action.gauche=false;
                break;
            case Keyboard::D :
                action.droite=false;
                break;
            case Keyboard::Up :
                action.accelere=false;
                break;
            case Keyboard::Down :
                action.freine=false;
                break;
            case Keyboard::Left :
                action.gauche=false;
                break;
            case Keyboard::Right :
                action.droite=false;
                break;
            default:
                break;
        }
    }
}