all: bin/Vroum

bin/Vroum: obj/main.o obj/Voiture.o obj/Moteur.o obj/Roues.o obj/Physique.o obj/Terrain.o obj/Jeu.o
	g++ obj/main.o obj/Voiture.o obj/Moteur.o obj/Roues.o obj/Physique.o obj/Terrain.o obj/Jeu.o -o bin/Vroum

obj/main.o: src/main.cpp src/Voiture.h src/Moteur.h src/Roues.h src/Physique.h src/Terrain.h src/Jeu.h
	g++ -g -Wall -c src/main.cpp -o obj/main.o

obj/Jeu.o: src/Jeu.cpp src/Jeu.h src/Terrain.h src/Voiture.h src/Moteur.h src/Roues.h src/Physique.h
	g++ -g -Wall -c src/Jeu.cpp -o obj/Jeu.o

obj/Terrain.o: src/Terrain.cpp src/Terrain.h
	g++ -g -Wall -c src/Terrain.cpp -o obj/Terrain.o

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
	rm -f *.txt
	rm -f *.json