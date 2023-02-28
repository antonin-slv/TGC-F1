Vroum: main.o Voiture.o Moteur.o Roues.o
	g++ main.o Voiture.o Moteur.o Roues.o -o Vroum

main.o: main.cpp
	g++ -Wall -c main.cpp

Voiture.o: Voiture.cpp Voiture.h
	g++ -Wall -c Voiture.cpp

Moteur.o: Moteur.cpp Moteur.h
	g++ -Wall -c Moteur.cpp

Roues.o: Roues.cpp Roues.h
	g++ -Wall -c Roues.cpp
