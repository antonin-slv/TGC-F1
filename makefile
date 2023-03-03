all: bin/Vroum

bin/Vroum: obj/main.o obj/Voiture.o obj/Moteur.o obj/Roues.o obj/Physique.o obj/terrain.o obj/jeu.o
	g++ obj/main.o obj/Voiture.o obj/Moteur.o obj/Roues.o obj/Physique.o -o bin/Vroum

obj/main.o: src/main.cpp src/Voiture.h src/Moteur.h src/Roues.h src/Physique.h src/terrain.h src/jeu.h
	g++ -g -Wall -c src/main.cpp -o obj/main.o

obj/jeu.o: src/jeu.cpp src/jeu.h src/terrain.h src/Voiture.h src/Moteur.h src/Roues.h src/Physique.h
	g++ -g -Wall -c src/jeu.cpp -o obj/jeu.o

obj/terrain.o: src/terrain.cpp src/terrain.h
	g++ -g -Wall -c src/terrain.cpp -o obj/terrain.o

obj/Voiture.o: src/Voiture.cpp src/Voiture.h src/Moteur.h src/Roues.h src/Physique.h
	g++ -g -Wall -c src/Voiture.cpp -o obj/Voiture.o

obj/Moteur.o: src/Moteur.h
	g++ -g -Wall -c src/Moteur.cpp -o obj/Moteur.o

obj/Roues.o: src/Roues.h 
	g++ -g -Wall -c src/Roues.cpp -o obj/Roues.o


obj/Physique.o: src/Physique.cpp src/Physique.h
	g++ -g -Wall -c src/Physique.cpp -o obj/Physique.o

clean:
	rm -f obj/*
	rm -f bin/*