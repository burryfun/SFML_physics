all: main

main: main.o App.o Object.o Surface.o Line.o Circle.o Shape.o Core.o
	g++ App.o Object.o Surface.o Line.o Circle.o Shape.o Core.o main.o -o main -lsfml-graphics -lsfml-window -lsfml-system

main.o: main.cpp
	g++ -c main.cpp

App.o: App.cpp
	g++ -c App.cpp

Object.o: Object.cpp
	g++ -c Object.cpp

Surface.o: Surface.cpp
	g++ -c Surface.cpp
Line.o: Line.cpp
	g++ -c Line.cpp

Circle.o: Circle.cpp
	g++ -c Circle.cpp

Shape.o: Shape.cpp
	g++ -c Shape.cpp

Core.o: Core.cpp
	g++ -c Core.cpp

clean:
	rm -rf *.o
