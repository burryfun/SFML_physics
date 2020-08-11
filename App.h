#include <SFML/Graphics/VertexArray.hpp>
#include <iostream>
#include <vector>
#include <cmath>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include "Circle.h"
#include "Core.h"
#include "Object.h"
#include "Surface.h"
#include "Line.h"
#include "Shape.h"

class App
{
public:
	App();
	~App();
	sf::Clock clock;	
	std::vector<Shape*> shapes;
	Core* core;
	std::vector <Line*> lines;
	//Surface surface;
	const bool			running() const;
	void				pollEvents();
	void				collisionCircleLine(Object* circle, Line* line);	
	void				update();
	void				render();
private:
	sf::VideoMode		videoMode;
	sf::RenderWindow*	window;
	sf::Event			sfmlEvent;
	void				initWindow();
};
