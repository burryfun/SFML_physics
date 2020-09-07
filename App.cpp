#include "App.h"
#include "Circle.h"
#include "Line.h"
#include "Object.h"
#include "Shape.h"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/PrimitiveType.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/System/Vector2.hpp>


const bool App::running() const
{
	return window->isOpen();
}

void App::initWindow()
{
	videoMode = sf::VideoMode(800, 600);
	window = new sf::RenderWindow(videoMode, "Simple physics", sf::Style::Default);	
	window->setFramerateLimit(60);
	
	core = new Core();
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
		// CORE POLL EVENTS
		core->pollEvents(*window,sfmlEvent);
		
		// WINDOW EVENTS
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
		}
	}	
}



void App::collisionCircleLine(Object* circle, Line* line)
{
	sf::Vector2f p = sf::Vector2f(circle->getPosition());	//center of circle
	sf::Vector2f s = line->getPoints()[0].position;			//point at start of line
	sf::Vector2f e = line->getPoints()[1].position;			//point at ent of line
	sf::Vector2f ps = p - s;
	sf::Vector2f se = e - s;
	float lengthLine = (e.x - s.x) * (e.x - s.x) + (e.y - s.y) * (e.y - s.y);
	float t = ((ps.x * se.x) + (ps.y * se.y)) /	lengthLine; //point of normal on line
	sf::Vector2f st;
	st.x = s.x + t*se.x;
	st.y = s.y + t*se.y;

	sf::Vector2f distance = p - st;
	float distanceBetween = sqrtf((distance.x*distance.x) + (distance.y*distance.y));
	
	sf::Vector2f normal = distance / distanceBetween;
	float dotProductNormal = circle->getVelocity().x*normal.x + 
								circle->getVelocity().y*normal.y;
	
	sf::Vector2f tangential = sf::Vector2f(-normal.y, normal.x);
	float dotProductTangential = circle->getVelocity().x*tangential.x + 
									circle->getVelocity().y * tangential.y;

	if (distanceBetween <= circle->getRadius())
	{
		if (t > -0.f && t < 1.f)
		{
			circle->setVelocity(sf::Vector2f(-normal.x*dotProductNormal + tangential.x*dotProductTangential,
												-normal.y*dotProductNormal + tangential.y*dotProductTangential));
		
			float overlap = distanceBetween - circle->getRadius();
			circle->setPosition(p.x - distance.x * overlap / distanceBetween, 
									p.y -distance.y * overlap / distanceBetween);
		}
	}

}

void App::update()
{
	float deltaTime = 0.f;
	deltaTime = clock.restart().asSeconds();
	pollEvents();
	/*for (auto circle : circles)
	{
		for (auto circle2 : circles)
		{
			collisionObjects(circle, circle2);
		}
		for (auto line : lines)
		{
			collisionCircleLine(circle, line);
		}
		if (dragged)
		{
			dragging(draggedCircle);
		}
		else
		{	
			force[0].position = sf::Vector2f(0.f, 0.f);
			force[1].position = sf::Vector2f(0.f, 0.f);
		}
		circle->update(*window,	deltaTime);
	}
	*/
	core->update(*window, deltaTime);
}

void App::render()
{
	window->clear();
	window->draw(*core);
	window->display();
}
