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
#include <math.h>

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

void App::collisionObjects(Object* obj1, Object* obj2)
{
	sf::Vector2f velocity1 = obj1->getVelocity();
	sf::Vector2f distance = obj1->getPosition() - obj2->getPosition();
	float distanceBetween = (sqrtf((distance.x*distance.x) + (distance.y*distance.y)));
	if (obj1 != obj2)
	{
		if (sqrtf((distance.x*distance.x) + (distance.y*distance.y)) - (obj1->getRadius()+obj2->getRadius()) < 0.f)
		{

			float overlap = (distanceBetween - obj1->getRadius() - obj2->getRadius()) / 2.f;
			float moveX = (overlap * (obj1->getPosition().x - obj2->getPosition().x) / distanceBetween);
			float moveY = (overlap * (obj1->getPosition().y - obj2->getPosition().y) / distanceBetween);	
			obj1->setPosition(obj1->getPosition().x - moveX, obj1->getPosition().y - moveY);
			obj2->setPosition(obj2->getPosition().x +  moveX, obj2->getPosition().y + moveY);

			sf::Vector2f normal;
			normal.x = distance.x / distanceBetween;
			normal.y = distance.y / distanceBetween;

			sf::Vector2f tangential;
			tangential.x = -normal.y;
			tangential.y =  normal.x;

			float dotProductTangential1 = obj1->getVelocity().x*tangential.x + obj1->getVelocity().y*tangential.y;
			float dotProductTangential2 = obj2->getVelocity().x*tangential.x + obj2->getVelocity().y*tangential.y;
			
			float dotProductNormal1 = obj1->getVelocity().x*normal.x + obj1->getVelocity().y*normal.y;
			float dotProductNormal2 = obj2->getVelocity().x*normal.x + obj2->getVelocity().y*normal.y;

			obj1->setVelocity(dotProductTangential1*tangential + (2*obj2->getMass()*dotProductNormal2*normal +
								dotProductNormal1*normal*(obj1->getMass()-obj2->getMass())) / 
									(obj1->getMass()+obj2->getMass()));
			obj2->setVelocity(dotProductTangential2*tangential + (2*obj1->getMass()*dotProductNormal1*normal +
								dotProductNormal2*normal*(obj1->getMass()-obj2->getMass())) / 
									(obj1->getMass()+obj2->getMass()));
			
			//obj2->setVelocity(dotProductTangential2*tangential);
			
			//obj1->setVelocity( 2.f*obj2->getMass()/(obj1->getMass()+obj2->getMass())*obj2->getVelocity() + velocity1*(obj1->getMass()-obj2->getMass())/(obj1->getMass() + obj2->getMass()) );
		}
	}
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
		for (auto circle2 : circles)
		{
			collisionObjects(circle, circle2);
			//circle->updateCollisionObjects(circle2);	
		}
		circle->update(*window, clock.restart().asSeconds());
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
