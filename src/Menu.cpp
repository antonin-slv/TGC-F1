#include <iostream>
#include "Menu.h"
#include <string>
#include <SFML/Audio.hpp>

using namespace std;
using namespace sf;

//DEFINITION DES FONCTIONS=========================================================================

void initBoutonCentre(RenderWindow & window, RectangleShape & rectangle, int y, int largeur, int hauteur){
    rectangle.setFillColor(Color::Transparent);
    rectangle.setOutlineThickness(3);
    rectangle.setOutlineColor(Color::White);
    rectangle.setSize(Vector2f(largeur,hauteur));
    rectangle.setPosition((window.getSize().x-largeur)/2, y);
}

void initCurseur(RenderWindow & window, RectangleShape & rectangle, int y, int largeur, int hauteur){
    initBoutonCentre(window, rectangle, y, largeur, hauteur);
    rectangle.setFillColor(Color::White);
}

void initTexteCentre(RenderWindow & window, Text & texte, Font & font, int taille, string txt, int y){
    texte.setFont(font);
    texte.setCharacterSize(taille);
    texte.setString(txt);
    texte.setFillColor(Color::White);
    texte.setPosition((window.getSize().x-texte.getLocalBounds().width)/2, y+15);
}

void initTitre(RenderWindow & window, Text & texte, Font & font, int taille, string txt, int y){
    initTexteCentre(window, texte, font, taille, txt, y);
    texte.setFillColor(Color::Red);
}

bool estSelectionne(RenderWindow & window, RectangleShape & rectangle){
    return rectangle.getGlobalBounds().contains(Mouse::getPosition(window).x, Mouse::getPosition(window).y);
}

void colorerSelectionne(RectangleShape & rectangle){
    rectangle.setFillColor(Color(32,32,32));
    rectangle.setOutlineColor(Color::Red);
}

void colorerNonSelectionne(RectangleShape & rectangle){
    rectangle.setFillColor(Color::Transparent);
    rectangle.setOutlineColor(Color::White);
}


json get_liste_circuit() {
    ifstream fich_liste;
    fich_liste.open("data/liste_niveaux.json");
    //on charge la liste des niveaux dans un objet json
    json liste_niveaux;
    fich_liste >> liste_niveaux;
    fich_liste.close();//le fichier, ouvert en lecture, n'est plus utile
    return liste_niveaux;
}

bool get_parametre_circuit(Selection & parametre_jeu) {
    
    json liste_niveaux=get_liste_circuit();
    //si le circuit existe dans la liste, on actualise le chemin du circuit et le nombre de tours
    unsigned int i = 0;
    for (auto niveau : liste_niveaux) {
        if (niveau["nom"] == parametre_jeu.nom_circuit) {
            parametre_jeu.chemin_circuit = niveau["path"];
            parametre_jeu.nb_tours = niveau["nombreTour"];
            return true;
        }
        i++;
        parametre_jeu.indice_circuit=i;//si le circuit n'existe pas, indice = nombre de circuits dans la liste
    }
    return false;//sinon on signal que le circuit n'existe pas
}

void boucleMenu(RenderWindow & window, Selection & parametre_jeu){

    //INITIALISATION===============================================================================

    window.setView(window.getDefaultView());

    bool parametre = false;
    bool choix_niveau = false;

    Music music;
    music.openFromFile("data/sounds/menu.wav");
    music.setVolume(parametre_jeu.volume/2);
    music.setLoop(true);
    music.play();

    Clock buttonPressed;

    //RECTANGLES===================================================================================

    //section menu principal
    RectangleShape boutonJouer;
    initBoutonCentre(window, boutonJouer, 450, 400, 100);

    RectangleShape boutonEditeur;
    initBoutonCentre(window, boutonEditeur, 600, 400, 100);

    RectangleShape boutonParametre;
    initBoutonCentre(window, boutonParametre, 750, 400, 100);

    RectangleShape boutonQuitter;
    initBoutonCentre(window, boutonQuitter, 900, 400, 100);

    //section parametre
    RectangleShape barreVolume;
    initBoutonCentre(window, barreVolume, 300, 600, 10);

    RectangleShape barreVolume2;
    initCurseur(window, barreVolume2, 300, 600, 10);

    RectangleShape curseurVolume;
    initCurseur(window, curseurVolume, 300, 10, 30);

    RectangleShape barreDecalage;
    initBoutonCentre(window, barreDecalage, 500, 600, 10);

    RectangleShape barreDecalage2;
    initCurseur(window, barreDecalage2, 500, 600, 10);

    RectangleShape curseurDecalage;
    initCurseur(window, curseurDecalage, 500, 10, 30);

    //commun aux sous menus
    RectangleShape boutonRetour;
    initBoutonCentre(window, boutonRetour, 900, 400, 100);

    //section choix niveau
    vector<RectangleShape> boutonsNiveaux(5);
    for(int i=0; i<5; i++){
        initBoutonCentre(window, boutonsNiveaux[i], i*150+100, 300, 75);
    }

    //TEXTES=======================================================================================

    Font font;
    font.loadFromFile("data/fonts/F1.ttf");

    Text texteTitre;
    initTitre(window, texteTitre, font, 100, "The Great Competition", 50);

    Text texteSousTitre;
    initTitre(window, texteSousTitre, font, 100, "Fast One", 175);

    Text texteJouer;
    initTexteCentre(window, texteJouer, font, 50, "Jouer", 450);

    Text texteEditeur;
    initTexteCentre(window, texteEditeur, font, 50, "Editeur", 600);

    Text texteParametre;
    initTexteCentre(window, texteParametre, font, 50, "Parametres", 750);

    Text texteQuitter;
    initTexteCentre(window, texteQuitter, font, 50, "Quitter", 900);

    Text texteCredits;
    initTexteCentre(window, texteCredits, font, 25, "version alpha", 0);
    texteCredits.setPosition(window.getSize().x*0.84, window.getSize().y*0.9); 

    Text texteCredits2;
    initTexteCentre(window, texteCredits2, font, 25, "by Ninotnas & Sipior", 0);
    texteCredits2.setPosition(window.getSize().x*0.84, window.getSize().y*0.95);

    Text texteVolume;
    initTexteCentre(window, texteVolume, font, 50, "Volume : " + to_string(parametre_jeu.volume), 200);

    Text texteDecalage;
    initTexteCentre(window, texteDecalage, font, 50, "Decalage : " + to_string(parametre_jeu.decalage), 600);

    Text texteConseil;
    initTexteCentre(window, texteConseil, font, 25, "Pour regler le volume, utilisez les fleches HAUT et BAS", 700);

    Text texteConseil2;
    initTexteCentre(window, texteConseil2, font, 25, "Pour regler le decalage, utilisez les fleches GAUCHE et DROITE", 750);

    Text texteRetour;
    initTexteCentre(window, texteRetour, font, 50, "Retour", 900);

    vector<Text> textesNiveaux(5);
    for(int i=0; i<5; i++){
        initTexteCentre(window, textesNiveaux[i], font, 35, "Niveau " + to_string(i+1), i*150+100);
    }

    //IMAGES DE FOND================================================================================
    Texture fond;
    fond.loadFromFile("data/images/fond.png");
    fond.setSmooth(true);

    Texture fond2;
    fond2.loadFromFile("data/images/fond2.png");
    fond2.setSmooth(true);
    
    Sprite spriteFond(fond);
    spriteFond.setScale(0.4, 0.4);
    spriteFond.setPosition(window.getSize().x-spriteFond.getGlobalBounds().width, (window.getSize().y-spriteFond.getGlobalBounds().height)*0.6);
    
    Sprite spriteFond2(fond2);
    spriteFond2.setScale(0.4, 0.4);
    spriteFond2.setPosition(0, (window.getSize().y-spriteFond.getGlobalBounds().height)*0.6);
    //BOUCLE PRINCIPALE============================================================================
    while (window.isOpen()){
        Event event;
        while (window.pollEvent(event)){
            if (event.type == Event::Closed){
                window.close();
            }
            if(!parametre and !choix_niveau){ //Menu principal ======================================================
                if (event.type == Event::MouseButtonPressed && buttonPressed.getElapsedTime().asMilliseconds() > 200){
                    if (event.mouseButton.button == Mouse::Left){
                        buttonPressed.restart();
                        if (estSelectionne(window, boutonJouer)){
                            choix_niveau = true;
                        }
                        if (estSelectionne(window, boutonEditeur)){
                            
                            parametre_jeu.choix="editeur";
                            parametre_jeu.chemin_circuit=get_liste_circuit()[0]["path"];
                            return;
                        }
                        if (estSelectionne(window, boutonParametre)){
                            parametre = true;
                        }
                        if (estSelectionne(window, boutonQuitter)){
                            parametre_jeu.choix="quitter";
                            return;
                        }
                    }
                }
                if(estSelectionne(window, boutonJouer)){
                    colorerSelectionne(boutonJouer);
                }
                else{
                    colorerNonSelectionne(boutonJouer);
                }

                if(estSelectionne(window, boutonEditeur)){
                    colorerSelectionne(boutonEditeur);
                }
                else{
                    colorerNonSelectionne(boutonEditeur);
                }
                
                if(estSelectionne(window, boutonParametre)){
                    colorerSelectionne(boutonParametre);
                }
                else{
                    colorerNonSelectionne(boutonParametre);
                }

                if(estSelectionne(window, boutonQuitter)){
                    colorerSelectionne(boutonQuitter);
                }
                else{
                    colorerNonSelectionne(boutonQuitter);
                }
            }
            if(choix_niveau){
                if (event.type == Event::MouseButtonPressed && buttonPressed.getElapsedTime().asMilliseconds() > 200){
                    if (event.mouseButton.button == Mouse::Left){
                        buttonPressed.restart();
                        for(int i=0; i<5; i++){
                            if (estSelectionne(window, boutonsNiveaux[i])){
                                parametre_jeu.nom_circuit = "niveau_" + to_string(i+1);
                                if ( get_parametre_circuit(parametre_jeu) ) {
                                    parametre_jeu.choix="Jouer";
                                    return;
                                }
                            }
                        }
                        if(estSelectionne(window, boutonRetour)){
                            choix_niveau = false;
                        }
                    }
                }
                for(int i=0; i<5; i++){
                    if(estSelectionne(window, boutonsNiveaux[i])) {
                        colorerSelectionne(boutonsNiveaux[i]);
                    }
                    else{
                        colorerNonSelectionne(boutonsNiveaux[i]);
                    }
                    if(estSelectionne(window, boutonRetour)){
                        colorerSelectionne(boutonRetour);
                    }
                    else{
                        colorerNonSelectionne(boutonRetour);
                    }
                }
            }
            if(parametre){ //Menu parametre ================================================================
                if(event.type == Event::KeyPressed){
                    if(event.key.code == Keyboard::Escape){
                        choix_niveau = false;
                        parametre = false;
                    }
                }
                if (event.type == Event::MouseButtonPressed && buttonPressed.getElapsedTime().asMilliseconds() > 200){
                    if (event.mouseButton.button == Mouse::Left){
                        buttonPressed.restart();
                        if (estSelectionne(window, boutonRetour)){
                            choix_niveau = false;
                            parametre = false;
                        }
                    }
                }
                if(estSelectionne(window, boutonRetour)){
                    colorerSelectionne(boutonRetour);
                }
                else{
                    colorerNonSelectionne(boutonRetour);
                }
                if(Keyboard::isKeyPressed(Keyboard::Up)){
                    if(parametre_jeu.volume < 96){
                        parametre_jeu.volume += 5;
                    }
                    else{
                        parametre_jeu.volume = 100;
                    }
                }
                if(Keyboard::isKeyPressed(Keyboard::Down)){
                    if(parametre_jeu.volume > 4){
                        parametre_jeu.volume -= 5;
                    }
                    else{
                        parametre_jeu.volume = 0;
                    }
                }
                if(Keyboard::isKeyPressed(Keyboard::Right)){
                    if(parametre_jeu.decalage < 4.5){
                        parametre_jeu.decalage += 0.5;
                    }
                    else{
                        parametre_jeu.decalage = 5;
                    }
                }
                if(Keyboard::isKeyPressed(Keyboard::Left)){
                    if(parametre_jeu.decalage > 0){
                        parametre_jeu.decalage -= 0.5;
                    }
                    else{
                        parametre_jeu.decalage = 0;
                    }
                }
            }
        }


        //AFFICHAGE================================================================================================
        window.clear(Color::Black);
        window.draw(spriteFond);
        window.draw(spriteFond2);

        if(!parametre and !choix_niveau){
            window.draw(texteTitre);
            window.draw(texteSousTitre);
            window.draw(boutonJouer);
            window.draw(boutonEditeur);
            window.draw(boutonParametre);
            window.draw(boutonQuitter);
            window.draw(texteJouer);
            window.draw(texteEditeur);
            window.draw(texteParametre);
            window.draw(texteQuitter);
            window.draw(texteCredits);
            window.draw(texteCredits2);
        }
        if(choix_niveau){
            for(int i = 0; i < 5; i++){
                window.draw(boutonsNiveaux[i]);
                window.draw(textesNiveaux[i]);
            }
            window.draw(boutonRetour);
            window.draw(texteRetour);
        }
        if(parametre){
            texteVolume.setString("Volume : " + to_string(parametre_jeu.volume) + "%");
            texteVolume.setPosition((window.getSize().x-texteVolume.getGlobalBounds().width)/2,200);

            barreVolume2.setSize(Vector2f(6*parametre_jeu.volume,10));
            curseurVolume.setPosition((1320-curseurVolume.getGlobalBounds().width)/2+6*parametre_jeu.volume,290);

            texteDecalage.setString("Decalage : " + to_string(parametre_jeu.decalage));
            texteDecalage.setPosition((window.getSize().x-texteDecalage.getGlobalBounds().width)/2,400);

            barreDecalage2.setSize(Vector2f(120*parametre_jeu.decalage,10));
            curseurDecalage.setPosition((1320-curseurDecalage.getGlobalBounds().width)/2+120*parametre_jeu.decalage,490);

            window.draw(texteVolume);
            window.draw(barreVolume);
            window.draw(barreVolume2);
            window.draw(curseurVolume);
            window.draw(texteDecalage);
            window.draw(barreDecalage);
            window.draw(barreDecalage2);
            window.draw(curseurDecalage);
            window.draw(texteConseil);
            window.draw(texteConseil2);
            window.draw(boutonRetour);
            window.draw(texteRetour);
        }
        
        music.setVolume(parametre_jeu.volume/2);
        window.display();
    }

    music.stop();
    return;
}


bool sauvegarderTemp(Selection const & param, float temps) {
    
    ifstream fich_liste("data/liste_niveaux.json");
    json liste_niveaux;
    fich_liste >> liste_niveaux;
    fich_liste.close();
    
    cout<<endl<<"Vous avez fait : "<<temps<<" secondes"<<endl;
    cout<<"liste des temps :"<<endl;
    if (liste_niveaux[param.indice_circuit].contains("listeTemps"))
    {   for (auto temps_ : liste_niveaux[param.indice_circuit]["listeTemps"]) {
            cout << "   "<<temps_["nom"] << " : " << temps_["temps"] << endl;
        }
    }
    else cout << "   aucun temps enregistré" << endl;

    string pseudo;
    if (temps < 2.0) {
        cout<<"Eh ben, il faut le finir le circuit !"<<endl;
        cout<<"entrez n'importe quoi pour continuer : ";
        cin>>pseudo;
        return false;
    }
    cout << "Enregistrer votre temps ? (y/n) :";
    cin >> pseudo;
    if (pseudo != "y" && pseudo != "Y") return false;

    cout << "Entrez votre pseudo : ";
    cin>>pseudo;
    json nouveau_temps;
    nouveau_temps["nom"] = pseudo;
    nouveau_temps["temps"] = temps;
    liste_niveaux[param.indice_circuit]["listeTemps"].push_back(nouveau_temps);

    ofstream fichier("data/liste_niveaux.json");
    fichier << liste_niveaux.dump(4);
    fichier.close();
    return true;
}