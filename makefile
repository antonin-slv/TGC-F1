CFLAGS = -Wall -g
HVOITURE = src/Voiture.h src/Moteur.h src/Roues.h src/Physique.h
HEDITEUR = src/Editeur.h src/Terrain.h
HINTERFACE = src/Affichage.h src/Menu.h

OVOITURE= obj/Voiture.o obj/Moteur.o obj/Roues.o obj/Physique.o
OEDITEUR= obj/Editeur.o obj/Terrain.o
OINTERFACE= obj/Affichage.o obj/Menu.o

EXECUTABLE = bin/Vroum

all: $(EXECUTABLE)

voiture : obj/Voiture.o

editeur : obj/Editeur.o

$(EXECUTABLE): obj/main.o $(OVOITURE) $(OEDITEUR) $(OINTERFACE) obj/Jeu.o obj/Collision.o
	g++ obj/main.o $(OVOITURE) $(OEDITEUR) $(OINTERFACE) obj/Jeu.o -o $(EXECUTABLE)

obj/main.o: src/main.cpp $(HVOITURE) $(HEDITEUR) $(HINTERFACE) src/Jeu.h src/Collision.h
	g++ $(CFLAGS) -c src/main.cpp -o obj/main.o

obj/Affichage.o: src/Affichage.cpp $(HINTERFACE) $(HVOITURE) $(HEDITEUR) src/Jeu.h
	g++ $(CFLAGS) -c src/Affichage.cpp -o obj/Affichage.o

obj/Jeu.o: src/Jeu.cpp src/Jeu.h src/Terrain.h $(HVOITURE) src/Collision.h
	g++ $(CFLAGS) -c src/Jeu.cpp -o obj/Jeu.o

obj/Editeur.o: src/Editeur.cpp $(HEDITEUR)
	g++ $(CFLAGS) -c src/Editeur.cpp -o obj/Editeur.o

obj/Terrain.o: src/Terrain.cpp src/Terrain.h
	g++ $(CFLAGS) -c src/Terrain.cpp -o obj/Terrain.o

obj/Collision.o: src/Collision.cpp src/Collision.h $(HVOITURE) src/Terrain.h
	g++ $(CFLAGS) -c src/Collision.cpp -o obj/Collision.o

obj/Voiture.o: src/Voiture.cpp $(HVOITURE)
	g++ $(CFLAGS) -c src/Voiture.cpp -o obj/Voiture.o

obj/Moteur.o: src/Moteur.h
	g++ $(CFLAGS) -c src/Moteur.cpp -o obj/Moteur.o

obj/Roues.o: src/Roues.h 
	g++ $(CFLAGS) -c src/Roues.cpp -o obj/Roues.o

obj/Physique.o: src/Physique.cpp src/Physique.h
	g++ $(CFLAGS) -c src/Physique.cpp -o obj/Physique.o

obj/Menu.o: src/Menu.cpp src/Menu.h
	g++ $(CFLAGS) -c src/Menu.cpp -o obj/Menu.o

clean:
	rm -f obj/*
	rm -f bin/*

clean_o_voiture:
	rm -f $(OVOITURE)

clean_o_editeur:
	rm -f $(OEDITEUR)

clean_o_interface:
	rm -f $(OINTERFACE)
