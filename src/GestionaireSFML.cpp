#include "GestionaireSFML.h"

#include <iostream>
#include <math.h>
using namespace std;
using namespace sf;

GestionSFML::GestionSFML() {       
    zoom = 1;
}

void GestionSFML::chargerNiveau(string path, int nb_tours) {
    
    ChargerTerrain(path,nb_tours);//réinitialise le jeu en Entier, et charge le terrain    
    interface.clearProps();//les props de l'interface, mais garde ses textures
    zoom = 1;
    interface.loadTerrain(terrain,"data/props/road.png");//charge le terrain dans l'interface (2e argument : inutlie pour le moment)


    tab_voit.clear();//on supprime les voitures du jeu
    //on crée une voiture temporaire pour l'interface et on la charge dans l'interface et le jeu
    Voiture Voit_temp = Voiture(Moteur(),Roues(),796,0.14,0,0,0,0,0,0,0);
    Voit_temp.setRotation(terrain.getLigneArrivee().getRotation()+M_PI/2);
    Voit_temp.setPos(terrain.getLigneArrivee().getPos());
    cout<<"position voiture :"<<Voit_temp.getPos().x<<" "<<Voit_temp.getPos().y<<endl;
    interface.loadVoiture(Voit_temp,"data/cars/F1.png");//attribue une hitbox à la voiture et la charge dans l'interface
    ajouterVoiture(Voit_temp);
}


GestionSFML::~GestionSFML()
{   tab_voit.clear();
    cout<<"fin destruction gestionnaire"<<endl;
}

string affiche_temps(float t){
    int minutes = floor(t/60);
    t-=minutes*60;
    int secondes = floor(t);
    t-=secondes;
    return to_string(minutes) + "\'" + to_string(secondes) + "\"" + to_string(int(t*1000));
}


sf::Time GestionSFML::boucleJeuSFML(RenderWindow & window, Clock & temps_au_tour, float decalage)
{
    temps_au_tour.restart();

    Clock clock;
    clock.restart();
    
    Clock frames;

    Font font;
    font.loadFromFile("data/fonts/Consolas.ttf");

    Text text;

    // select the font
    text.setFont(font); // font is a Font
    // set the character size
    text.setCharacterSize(50); // in pixels, not points!
    text.setScale(0.025,0.025);
    
    long int nb_frames = 0;
    float temps = 0;
    sf::Time temps_circuit = sf::seconds(0);

    cout << "debut ok" << endl;
    ActionClavier action;

    Text texte_temps_au_tour;
    texte_temps_au_tour.setFont(font);
    texte_temps_au_tour.setCharacterSize(50);
    texte_temps_au_tour.setScale(0.025,0.025);

    bool quitter = false;
    bool gagne = false;
    do {
    // On traite tous les évènements de la fenêtre qui ont été générés depuis la dernière itération de la boucle
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
        Vecteur pos=voit.getPos();
        if (!gagne){
            affichage=  "Tour : " + to_string(nb_tour) + " / " +to_string(nb_tour_max) + "\n" +
                        "Checkpoint : " + to_string(num_checkpoint) + " / " + to_string(terrain.getOrdreCheckpoint().size()) + "\n" +
                        "Vitesse : " + to_string(voit.getVitesse()*3.6) + " km/h \n" +
                        "Position : " + to_string(pos.x) + " , " + to_string(pos.y) + "\n" +
                        "Orientation : " + to_string(voit.getAngle()*180/M_PI) + "\n";
        }
        else affichage=  "Victoire ! \nTemps : " + to_string(temps_circuit.asSeconds()) + "\n";
        
        affichage+= "temps in game :" + to_string(temps) + " s\ncontre : " + to_string(clock.getElapsedTime().asSeconds()) + " s IRL\n";
        affichage+= "frame time : " + to_string(frame_time) + "\n"
                    "fps : " + to_string(1/frame_time) + "\n";
        
        text.setString(affichage);
        
        texte_temps_au_tour.setString("Temps ce tour : "+affiche_temps(temps_au_tour.getElapsedTime().asSeconds()));
        
        // On affiche le jeu
        afficherJeuSFML(window);
        
        View vue(interface.voiture.getPosition(), Vector2f(128.f, 72.f));
        vue.move(cos(voit.getAngle()) * voit.getVitesse() * decalage/24 ,decalage/24 * sin(voit.getAngle())*voit.getVitesse());
        window.setView(vue);
        afficherDebug(window, text);
        afficherDebug2(window, texte_temps_au_tour);
        window.display();
    } while (!quitter);
    cout << "nb frames : " << nb_frames << endl;
    cout << "temps : " << temps << endl;
    cout << "fps_moy : " << nb_frames/temps << endl<<endl;
    if (gagne) return temps_circuit;
    else return sf::seconds(-1);
}



void GestionSFML::afficherJeuSFML(RenderWindow & window)
{   
    window.clear(Color(0,200,0));
    interface.drawTerrain(window);

    sf::RectangleShape line(sf::Vector2f(tab_voit[0].getVitesse()/2.2/1.25, 0.5));
    line.setPosition(tab_voit[0].getPos().x, tab_voit[0].getPos().y);
    line.rotate(tab_voit[0].getAngle()*180/M_PI);
    window.draw(line);

    interface.drawVoitureHitbox(window,tab_voit[0]);
    interface.drawVoiture(window, tab_voit[0]);
}

void getActionClavier(Event event, ActionClavier & action)
{   if (event.type == Event::KeyPressed){
        switch (event.key.code){
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
    else if (event.type == Event::KeyReleased){

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