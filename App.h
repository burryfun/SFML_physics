#include <iostream>
#include <vector>
#include <cmath>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include "Object.h"
#include "Surface.h"

class App
{
public:
	App();
	~App();
	sf::Clock clock;	
	sf::CircleShape		shape;
	std::vector <Object*> circles;
	//Surface surface;
	const bool			running() const;
	bool				dragged = false;
	Object*				draggedCircle;
	sf::Vector2f		getMouseCoords();	
	void				pollEvents();
	void				dragging(Object* circle);
	void				collisionObjects(Object* obj1, Object* obj2);
	
	void				update();
	void				render();
private:
	sf::VideoMode		videoMode;
	sf::RenderWindow*	window;
	sf::Event			sfmlEvent;
	sf::Vector2f		m_mouse;
	sf::VertexArray		force; 
	void				initWindow();
};
