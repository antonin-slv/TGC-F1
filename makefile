all: bin/Vroum

bin/Vroum: obj/main.o obj/Voiture.o obj/Moteur.o obj/Roues.o
	g++ obj/main.o obj/Voiture.o obj/Moteur.o obj/Roues.o -o bin/Vroum

obj/main.o: src/main.cpp src/Voiture.h src/Moteur.h src/Roues.h
	g++ -g -Wall -c src/main.cpp -o obj/main.o

obj/Voiture.o: src/Voiture.cpp src/Voiture.h src/Moteur.h src/Roues.h
	g++ -g -Wall -c src/Voiture.cpp -o obj/Voiture.o

obj/Moteur.o: src/Moteur.h
	g++ -g -Wall -c src/Moteur.cpp -o obj/Moteur.o

obj/Roues.o: src/Roues.h 
	g++ -g -Wall -c src/Roues.cpp -o obj/Roues.o

clean:
	rm -f obj/*
	rm -f bin/*