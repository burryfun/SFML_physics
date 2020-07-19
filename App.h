#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <iostream>

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
	float time = 1/60.f;
	sf::Clock clock;	
	const bool running() const;
	void pollEvents();
	sf::CircleShape shape;
	Object circle;
	//Surface surface;
	
	sf::Vector2f getMouseCoords();

	void update();
	void render();
private:
	sf::VideoMode videoMode;
	sf::RenderWindow* window;
	sf::Event sfmlEvent;
	sf::Vector2f m_mouse;

	void initWindow();
};
