CFLAGS = -Wall -g
CC = g++

PATH_VOIT = src/Voiture/
EXTERNAL = src/External/

ISFML = -I/usr/include/SFML
LIBSFML= -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio



HVOITURE = $(PATH_VOIT)Voiture.h $(PATH_VOIT)Moteur.h $(PATH_VOIT)Roues.h $(PATH_VOIT)Physique.h $(PATH_VOIT)Vecteur.h
HEDITEUR = src/Editeur.h src/Terrain.h $(PATH_VOIT)Vecteur.h
HINTERFACE = src/GestionaireSFML.h src/Menu.h src/Interface.h

OVOITURE= obj/Voiture.o obj/Moteur.o obj/Roues.o obj/Physique.o obj/Vecteur.o
OEDITEUR= obj/Editeur.o obj/Terrain.o
OINTERFACE= obj/GestionaireSFML.o obj/Menu.o obj/Interface.o

EXECUTABLETXT = bin/VroumTXT
EXECUTABLESFML = bin/VroumSFML

all: $(EXECUTABLETXT) $(EXECUTABLESFML)

SFML : $(EXECUTABLESFML)

TXT : $(EXECUTABLETXT)

$(EXECUTABLESFML): obj/mainSFML.o $(OVOITURE) $(OEDITEUR) $(OINTERFACE) obj/Jeu.o obj/Collision.o
	$(CC) obj/mainSFML.o $(OVOITURE) $(OEDITEUR) $(OINTERFACE) obj/Jeu.o obj/Collision.o $(LIBSFML) -o $(EXECUTABLESFML)

$(EXECUTABLETXT): obj/mainTXT.o $(OVOITURE) $(OEDITEUR) obj/AffichageTXT.o obj/Jeu.o obj/Collision.o obj/winTxt.o
	$(CC) obj/mainTXT.o $(OVOITURE) $(OEDITEUR) obj/AffichageTXT.o obj/Jeu.o obj/Collision.o obj/winTxt.o -o $(EXECUTABLETXT)

obj/mainTXT.o: src/mainTXT.cpp $(HVOITURE) $(HEDITEUR) $(HINTERFACE) src/Jeu.h src/Collision.h $(EXTERNAL)winTxt.h
	$(CC) $(CFLAGS) -c src/mainTXT.cpp -o obj/mainTXT.o

obj/mainSFML.o: src/mainSFML.cpp $(HVOITURE) $(HEDITEUR) $(HINTERFACE) src/Jeu.h src/Collision.h
	$(CC) $(CFLAGS) -c src/mainSFML.cpp $(ISFML) -o obj/mainSFML.o

obj/AffichageTXT.o: src/AffichageTXT.cpp $(HINTERFACE) $(HVOITURE) src/Editeur.h src/Jeu.h $(EXTERNAL)winTxt.h
	$(CC) $(CFLAGS) -c src/AffichageTXT.cpp -o obj/AffichageTXT.o

obj/GestionaireSFML.o: src/GestionaireSFML.cpp $(HINTERFACE) $(HVOITURE) src/Jeu.h
	$(CC) $(CFLAGS) -c src/GestionaireSFML.cpp $(ISFML) -o obj/GestionaireSFML.o


obj/winTxt.o: $(EXTERNAL)winTxt.cpp $(EXTERNAL)winTxt.h
	$(CC) $(CFLAGS) -c $(EXTERNAL)winTxt.cpp -o obj/winTxt.o

obj/Jeu.o: src/Jeu.cpp src/Jeu.h src/Terrain.h $(HVOITURE) src/Collision.h
	$(CC) $(CFLAGS) -c src/Jeu.cpp -o obj/Jeu.o

obj/Interface.o: src/Interface.cpp src/Interface.h obj/Jeu.o obj/GestionaireSFML.o obj/Terrain.o
	$(CC) $(CFLAGS) -c src/Interface.cpp $(ISFML) -o obj/Interface.o

obj/Editeur.o: src/Editeur.cpp $(HEDITEUR) obj/Interface.o
	$(CC) $(CFLAGS) -c src/Editeur.cpp $(ISFML) -o obj/Editeur.o

obj/Terrain.o: src/Terrain.cpp src/Terrain.h $(PATH_VOIT)Vecteur.h 
	$(CC) $(CFLAGS) -c src/Terrain.cpp -o obj/Terrain.o

obj/Collision.o: src/Collision.cpp src/Collision.h $(HVOITURE) src/Terrain.h
	$(CC) $(CFLAGS) -c src/Collision.cpp -o obj/Collision.o

obj/Voiture.o: $(PATH_VOIT)Voiture.cpp $(HVOITURE)
	$(CC) $(CFLAGS) -c $(PATH_VOIT)Voiture.cpp -o obj/Voiture.o

obj/Moteur.o: $(PATH_VOIT)Moteur.h $(PATH_VOIT)Moteur.cpp
	$(CC) $(CFLAGS) -c $(PATH_VOIT)Moteur.cpp -o obj/Moteur.o

obj/Roues.o: $(PATH_VOIT)Roues.h $(PATH_VOIT)Roues.cpp
	$(CC) $(CFLAGS) -c $(PATH_VOIT)Roues.cpp -o obj/Roues.o

obj/Physique.o: $(PATH_VOIT)Physique.cpp $(PATH_VOIT)Physique.h
	$(CC) $(CFLAGS) -c $(PATH_VOIT)Physique.cpp -o obj/Physique.o

obj/Menu.o: src/Menu.cpp src/Menu.h
	$(CC) $(CFLAGS) -c src/Menu.cpp -o obj/Menu.o

obj/Vecteur.o: src/Voiture/Vecteur.cpp src/Voiture/Vecteur.h
	$(CC) $(CFLAGS) -c src/Voiture/Vecteur.cpp -o obj/Vecteur.o

clean:
	rm -f obj/*
	rm -f bin/*

lessclean :
	rm -f obj/*

clean_o_voiture:
	rm -f $(OVOITURE)

clean_o_editeur:
	rm -f $(OEDITEUR)

clean_o_interface:
	rm -f $(OINTERFACE)
