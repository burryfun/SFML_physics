#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <vector>

#include "Object.h"
#include "Surface.h"

class App
{
public:
	App();
	~App();
	sf::Clock clock;	
	const bool running() const;
	void pollEvents();
	sf::CircleShape shape;
	std::vector <Object*> circles;
	//Surface surface;
	bool dragged = false;
	Object* draggedCircle;
	void collisionObjects(Object* obj1, Object* obj2);
	void dragging(Object* circle);
	sf::Vector2f getMouseCoords();	
	
	void update();
	void render();
private:
	sf::VideoMode videoMode;
	sf::RenderWindow* window;
	sf::Event sfmlEvent;
	sf::Vector2f m_mouse;
	sf::VertexArray force; 
	void initWindow();
};
