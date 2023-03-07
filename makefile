all: bin/Vroum

bin/Vroum: obj/main.o obj/Voiture.o obj/Moteur.o obj/Roues.o obj/Physique.o obj/Terrain.o obj/Jeu.o obj/Menu.o obj/Editeur.o obj/Affichage.o obj/Collision.o
	g++ obj/main.o obj/Voiture.o obj/Moteur.o obj/Roues.o obj/Physique.o obj/Terrain.o obj/Jeu.o -o bin/Vroum

obj/main.o: src/main.cpp src/Voiture.h src/Moteur.h src/Roues.h src/Physique.h src/Terrain.h src/Jeu.h src/Menu.h src/Editeur.h src/Affichage.h
	g++ -g -Wall -c src/main.cpp -o obj/main.o

obj/Affichage.o: src/Affichage.cpp src/Affichage.h src/Voiture.h src/Terrain.h src/Jeu.h src/Editeur.h src/Menu.h
	g++ -g -Wall -c src/Affichage.cpp -o obj/Affichage.o

obj/Jeu.o: src/Jeu.cpp src/Jeu.h src/Terrain.h src/Voiture.h src/Collision.h src/Physique.h
	g++ -g -Wall -c src/Jeu.cpp -o obj/Jeu.o

obj/Editeur.o: src/Editeur.cpp src/Editeur.h src/Terrain.h
	g++ -g -Wall -c src/Editeur.cpp -o obj/Editeur.o

obj/Terrain.o: src/Terrain.cpp src/Terrain.h
	g++ -g -Wall -c src/Terrain.cpp -o obj/Terrain.o

obj/Collision.o: src/Collision.cpp src/Collision.h src/Voiture.h src/Terrain.h
	g++ -g -Wall -c src/Collision.cpp -o obj/Collision.o

obj/Voiture.o: src/Voiture.cpp src/Voiture.h src/Moteur.h src/Roues.h src/Physique.h
	g++ -g -Wall -c src/Voiture.cpp -o obj/Voiture.o

obj/Moteur.o: src/Moteur.h
	g++ -g -Wall -c src/Moteur.cpp -o obj/Moteur.o

obj/Roues.o: src/Roues.h 
	g++ -g -Wall -c src/Roues.cpp -o obj/Roues.o

obj/Physique.o: src/Physique.cpp src/Physique.h
	g++ -g -Wall -c src/Physique.cpp -o obj/Physique.o

obj/Menu.o: src/Menu.cpp src/Menu.h
	g++ -g -Wall -c src/Menu.cpp -o obj/Menu.o

clean:
	rm -f obj/*
	rm -f bin/*
	rm -f *.txt
	rm -f *.json