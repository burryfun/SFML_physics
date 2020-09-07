all: main

main: main.o App.o Core.o Object.o Surface.o Shape.o Circle.o Rect.o Line.o 
	g++ App.o Core.o Object.o Surface.o Shape.o Circle.o Rect.o  Line.o main.o -o main -lsfml-graphics -lsfml-window -lsfml-system

main.o: main.cpp
	g++ -c main.cpp

App.o: App.cpp
	g++ -c App.cpp

Core.o: Core.cpp
	g++ -c Core.cpp

Object.o: Object.cpp
	g++ -c Object.cpp

Surface.o: Surface.cpp
	g++ -c Surface.cpp

Shape.o: Shape.cpp
	g++ -c Shape.cpp

Circle.o: Circle.cpp
	g++ -c Circle.cpp

Rect.o: Rect.cpp
	g++ -c Rect.cpp

Line.o: Line.cpp
	g++ -c Line.cpp


clean:
	rm -rf *.o
