CFLAGS = -Wall -g
CC = g++

PATH_VOIT = src/Voiture/

HVOITURE = $(PATH_VOIT)Voiture.h $(PATH_VOIT)Moteur.h $(PATH_VOIT)Roues.h $(PATH_VOIT)Physique.h $(PATH_VOIT)Vecteur.h
HEDITEUR = src/Editeur.h src/Terrain.h $(PATH_VOIT)Vecteur.h
HINTERFACE = src/Affichage.h src/Menu.h

OVOITURE= obj/Voiture.o obj/Moteur.o obj/Roues.o obj/Physique.o obj/Vecteur.o
OEDITEUR= obj/Editeur.o obj/Terrain.o
OINTERFACE= obj/Affichage.o obj/Menu.o

EXECUTABLE = bin/Vroum

all: $(EXECUTABLE)

voiture : obj/Voiture.o

editeur : obj/Editeur.o

$(EXECUTABLE): obj/main.o $(OVOITURE) $(OEDITEUR) $(OINTERFACE) obj/Jeu.o obj/Collision.o obj/winTxt.o
	$(CC) obj/main.o $(OVOITURE) $(OEDITEUR) $(OINTERFACE) obj/Jeu.o obj/Collision.o obj/winTxt.o -o $(EXECUTABLE)

obj/main.o: src/main.cpp $(HVOITURE) $(HEDITEUR) $(HINTERFACE) src/Jeu.h src/Collision.h src/winTxt.h
	$(CC) $(CFLAGS) -c src/main.cpp -o obj/main.o

obj/Affichage.o: src/Affichage.cpp $(HINTERFACE) $(HVOITURE) $(HEDITEUR) src/Jeu.h src/winTxt.h
	$(CC) $(CFLAGS) -c src/Affichage.cpp -o obj/Affichage.o

obj/winTxt.o: src/winTxt.cpp src/winTxt.h
	$(CC) $(CFLAGS) -c src/winTxt.cpp -o obj/winTxt.o

obj/Jeu.o: src/Jeu.cpp src/Jeu.h src/Terrain.h $(HVOITURE) src/Collision.h
	$(CC) $(CFLAGS) -c src/Jeu.cpp -o obj/Jeu.o

obj/Editeur.o: src/Editeur.cpp $(HEDITEUR)
	$(CC) $(CFLAGS) -c src/Editeur.cpp -o obj/Editeur.o

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
