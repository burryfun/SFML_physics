#include "App.h"
#include "Object.h"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/PrimitiveType.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/WindowStyle.hpp>

#include <cmath>

const bool App::running() const
{
	return window->isOpen();
}

void App::initWindow()
{
	videoMode = sf::VideoMode(800, 600);
	window = new sf::RenderWindow(videoMode, "Simple physics", sf::Style::Default);	
	window->setFramerateLimit(60);
	force = sf::VertexArray(sf::LinesStrip, 2);
}


void App::dragging(Object *circle)
{
	if (dragged)
	{
		force[0] = circle->getPosition();
		force[1] = m_mouse;
	}
	else
	{
		force[1] = circle->getPosition();
	}
}

App::App()
{
	initWindow();
}

App::~App()
{
	delete window;
}

void App::pollEvents()
{
	while (window->pollEvent(sfmlEvent))
	{
		switch (sfmlEvent.type)
		{
			case sf::Event::Closed:
				window->close(); 
				break;
			case sf::Event::KeyPressed:
				if (sfmlEvent.key.code == sf::Keyboard::Escape)
				{
					window->close();
				}
				break;
			case sf::Event::MouseButtonPressed:
				if (sfmlEvent.mouseButton.button == sf::Mouse::Left)
				{
					Object* newObject = new Object(m_mouse, 50);
					circles.push_back(newObject);
				}
				if (sfmlEvent.mouseButton.button == sf::Mouse::Right)
				{
					for (auto circle : circles)
					{
						if (circle->checkCollisionPoint(m_mouse))
						{
							draggedCircle = circle;
							dragged = true;
						}
					}	
				}
				break;
			case sf::Event::MouseButtonReleased:
				if (sfmlEvent.mouseButton.button == sf::Mouse::Right && dragged)
				{
					draggedCircle->setVelocity(sf::Vector2f((draggedCircle->getPosition().x - m_mouse.x)/40,
															(draggedCircle->getPosition().y - m_mouse.y)/40));
					dragged = false;
				}
				break;
			case sf::Event::MouseMoved:
				m_mouse.x = sfmlEvent.mouseMove.x;
				m_mouse.y = sfmlEvent.mouseMove.y;
				break;
		}
	}	
}

sf::Vector2f App::getMouseCoords()
{
	return m_mouse;
}

void App::update()
{
	pollEvents();
	//circle.rotate(1);
	for (auto circle : circles)
	{
		if (dragged)
		{
			dragging(draggedCircle);
		}
		else
		{	
			force[0].position = sf::Vector2f(0.f, 0.f);
			force[1].position = sf::Vector2f(0.f, 0.f);
		}
		circle->update(getMouseCoords(), *window, clock.getElapsedTime().asSeconds());
	}
}

void App::render()
{
	window->clear();
	
	//surface.render(window);
	for (auto circle : circles)
	{
		window->draw(*circle);
	}
	window->draw(force);	
	window->display();
}
