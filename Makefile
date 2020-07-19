all: main

main: main.o App.o Object.o Surface.o
	g++ App.o Object.o Surface.o main.o -o main -lsfml-graphics -lsfml-window -lsfml-system

main.o: main.cpp
	g++ -c main.cpp

App.o: App.cpp
	g++ -c App.cpp

Object.o: Object.cpp
	g++ -c Object.cpp

Surface.o: Surface.cpp
	g++ -c Surface.cpp

clean:
	rm -rf *.o
